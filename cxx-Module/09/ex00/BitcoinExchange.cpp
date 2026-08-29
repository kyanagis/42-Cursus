#include "BitcoinExchange.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace {

std::string trim(const std::string& text) {
	std::string::size_type first = text.find_first_not_of(" \t\r\n");
	if (first == std::string::npos) {
		return "";
	}
	std::string::size_type last = text.find_last_not_of(" \t\r\n");
	return text.substr(first, last - first + 1);
}

bool all_digits(const std::string& text) {
	if (text.empty()) {
		return false;
	}
	for (std::string::size_type i = 0; i < text.size(); ++i) {
		if (text[i] < '0' || text[i] > '9') {
			return false;
		}
	}
	return true;
}

bool is_leap_year(int year) {
	if (year % 400 == 0) {
		return true;
	}
	if (year % 100 == 0) {
		return false;
	}
	return year % 4 == 0;
}

bool is_valid_date(const std::string& date) {
	if (date.size() != 10 || date[4] != '-' || date[7] != '-') {
		return false;
	}
	std::string y = date.substr(0, 4);
	std::string m = date.substr(5, 2);
	std::string d = date.substr(8, 2);
	if (!all_digits(y) || !all_digits(m) || !all_digits(d)) {
		return false;
	}
	int month = std::atoi(m.c_str());
	int day = std::atoi(d.c_str());
	if (month < 1 || month > 12 || day < 1) {
		return false;
	}
	static const int days[12] =
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int limit = days[month - 1];
	if (month == 2 && is_leap_year(std::atoi(y.c_str()))) {
		limit = 29;
	}
	return day <= limit;
}

bool parse_value(const std::string& text, double& out) {
	char* end = 0;
	out = std::strtod(text.c_str(), &end);
	if (end == text.c_str() || *end != '\0') {
		return false;
	}
	return true;
}

bool is_input_header(const std::string& line) {
	std::string::size_type bar = line.find('|');
	if (bar == std::string::npos) {
		return false;
	}
	return trim(line.substr(0, bar)) == "date"
		&& trim(line.substr(bar + 1)) == "value";
}

}  // namespace

BitcoinExchange::BitcoinExchange() {
}

BitcoinExchange::BitcoinExchange(const std::string& database_path) {
	load_database(database_path);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
	: database_(other.database_) {
}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other) {
	if (this != &other) {
		database_ = other.database_;
	}
	return *this;
}

BitcoinExchange::~BitcoinExchange() {
}

void BitcoinExchange::load_database(const std::string& database_path) {
	std::ifstream file(database_path.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open database file.");
	}
	std::string line;
	std::getline(file, line);  // discard the "date,exchange_rate" header
	while (std::getline(file, line)) {
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos) {
			continue;
		}
		std::string date = trim(line.substr(0, comma));
		double rate = 0.0;
		if (is_valid_date(date) && parse_value(trim(line.substr(comma + 1)),
				rate)) {
			database_[date] = rate;
		}
	}
	if (database_.empty()) {
		throw std::runtime_error("Error: empty or invalid database.");
	}
}

double BitcoinExchange::get_rate(const std::string& date) const {
	std::map<std::string, double>::const_iterator it =
		database_.lower_bound(date);
	if (it != database_.end() && it->first == date) {
		return it->second;
	}
	if (it == database_.begin()) {
		throw std::runtime_error("no rate available before this date");
	}
	--it;
	return it->second;
}

void BitcoinExchange::evaluate_line(const std::string& line) const {
	std::string::size_type bar = line.find('|');
	if (bar == std::string::npos) {
		std::cout << "Error: bad input => " << line << '\n';
		return;
	}
	std::string date = trim(line.substr(0, bar));
	std::string raw = trim(line.substr(bar + 1));
	double value = 0.0;
	if (!is_valid_date(date) || !parse_value(raw, value)) {
		std::cout << "Error: bad input => " << line << '\n';
		return;
	}
	if (value < 0.0) {
		std::cout << "Error: not a positive number.\n";
		return;
	}
	if (value > 1000.0) {
		std::cout << "Error: too large a number.\n";
		return;
	}
	std::cout << date << " => " << value << " = "
		<< (value * get_rate(date)) << '\n';
}

void BitcoinExchange::process_file(const std::string& input_path) const {
	std::ifstream file(input_path.c_str());
	if (!file.is_open()) {
		throw std::runtime_error("Error: could not open file.");
	}
	std::string line;
	bool first = true;
	while (std::getline(file, line)) {
		if (first) {
			first = false;
			if (is_input_header(line)) {
				continue;
			}
		}
		if (!trim(line).empty()) {
			evaluate_line(line);
		}
	}
}
