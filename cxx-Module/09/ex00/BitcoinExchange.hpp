#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

// BitcoinExchange keeps the price database in an ordered std::map keyed by
// date. Because dates are stored as "YYYY-MM-DD" strings, their lexicographic
// order matches chronological order, so std::map::lower_bound gives the
// "closest lower date" lookup the subject asks for in logarithmic time.

class BitcoinExchange {
public:
	BitcoinExchange();
	explicit BitcoinExchange(const std::string& database_path);
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();

	void process_file(const std::string& input_path) const;
	double get_rate(const std::string& date) const;

private:
	std::map<std::string, double> database_;

	void load_database(const std::string& database_path);
	void evaluate_line(const std::string& line) const;
};

#endif
