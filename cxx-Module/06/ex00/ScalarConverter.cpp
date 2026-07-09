#include "ScalarConverter.hpp"

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

static double dbl_inf(void) {
	return std::numeric_limits<double>::infinity();
}

static double dbl_nan(void) {
	return std::numeric_limits<double>::quiet_NaN();
}

static bool dbl_is_nan(double value) {
	return value != value;
}

static bool dbl_is_inf(double value) {
	return value == dbl_inf() || value == -dbl_inf();
}

static bool is_char(const std::string& literal) {
	if (literal.size() == 1
		&& !std::isdigit(static_cast<unsigned char>(literal[0])))
		return true;
	if (literal.size() == 3 && literal[0] == '\'' && literal[2] == '\'')
		return true;
	return false;
}

static bool is_int(const std::string& literal) {
	std::string::size_type i;

	if (literal.empty())
		return false;
	i = 0;
	if (literal[i] == '+' || literal[i] == '-')
		++i;
	if (i == literal.size())
		return false;
	while (i < literal.size()) {
		if (!std::isdigit(static_cast<unsigned char>(literal[i])))
			return false;
		++i;
	}
	return true;
}

static bool is_valid_body(const std::string& body) {
	char* end;

	if (body.empty())
		return false;
	end = 0;
	std::strtod(body.c_str(), &end);
	return end != 0 && *end == '\0';
}

static bool is_float_literal(const std::string& literal) {
	if (literal == "nanf" || literal == "inff" || literal == "+inff"
		|| literal == "-inff")
		return true;
	if (literal.empty() || literal[literal.size() - 1] != 'f')
		return false;
	return is_valid_body(literal.substr(0, literal.size() - 1));
}

static bool is_double_literal(const std::string& literal) {
	if (literal == "nan" || literal == "inf" || literal == "+inf"
		|| literal == "-inf")
		return true;
	return is_valid_body(literal);
}

static double char_value(const std::string& literal) {
	if (literal.size() == 3)
		return static_cast<double>(static_cast<unsigned char>(literal[1]));
	return static_cast<double>(static_cast<unsigned char>(literal[0]));
}

static double float_value(const std::string& literal) {
	if (literal == "nanf")
		return dbl_nan();
	if (literal == "inff" || literal == "+inff")
		return dbl_inf();
	if (literal == "-inff")
		return -dbl_inf();
	return std::strtod(literal.substr(0, literal.size() - 1).c_str(), 0);
}

static double double_value(const std::string& literal) {
	if (literal == "nan")
		return dbl_nan();
	if (literal == "inf" || literal == "+inf")
		return dbl_inf();
	if (literal == "-inf")
		return -dbl_inf();
	return std::strtod(literal.c_str(), 0);
}

static bool parse_literal(const std::string& literal, double& value) {
	if (is_char(literal)) {
		value = char_value(literal);
		return true;
	}
	if (is_int(literal)) {
		value = std::strtod(literal.c_str(), 0);
		return true;
	}
	if (is_float_literal(literal)) {
		value = float_value(literal);
		return true;
	}
	if (is_double_literal(literal)) {
		value = double_value(literal);
		return true;
	}
	return false;
}

static void print_char(double value) {
	char c;

	std::cout << "char: ";
	if (dbl_is_nan(value) || dbl_is_inf(value)
		|| value < std::numeric_limits<char>::min()
		|| value > std::numeric_limits<char>::max()) {
		std::cout << "impossible" << '\n';
		return;
	}
	c = static_cast<char>(value);
	if (std::isprint(static_cast<unsigned char>(c)))
		std::cout << "'" << c << "'" << '\n';
	else
		std::cout << "Non displayable" << '\n';
}

static void print_int(double value) {
	std::cout << "int: ";
	if (dbl_is_nan(value) || dbl_is_inf(value)
		|| value < std::numeric_limits<int>::min()
		|| value > std::numeric_limits<int>::max())
		std::cout << "impossible" << '\n';
	else
		std::cout << static_cast<int>(value) << '\n';
}

static std::string with_decimal(double value, bool as_float) {
	std::ostringstream oss;
	std::string text;

	if (as_float)
		oss << static_cast<float>(value);
	else
		oss << value;
	text = oss.str();
	if (text.find('.') == std::string::npos
		&& text.find('e') == std::string::npos)
		text += ".0";
	return text;
}

static void print_float(double value) {
	std::cout << "float: ";
	if (dbl_is_nan(value)) {
		std::cout << "nanf" << '\n';
		return;
	}
	if (dbl_is_inf(value)) {
		if (value < 0)
			std::cout << "-inff" << '\n';
		else
			std::cout << "inff" << '\n';
		return;
	}
	std::cout << with_decimal(value, true) << "f" << '\n';
}

static void print_double(double value) {
	std::cout << "double: ";
	if (dbl_is_nan(value)) {
		std::cout << "nan" << '\n';
		return;
	}
	if (dbl_is_inf(value)) {
		if (value < 0)
			std::cout << "-inf" << '\n';
		else
			std::cout << "inf" << '\n';
		return;
	}
	std::cout << with_decimal(value, false) << '\n';
}

void ScalarConverter::convert(const std::string& literal) {
	double value;

	value = 0.0;
	if (!parse_literal(literal, value)) {
		std::cout << "char: impossible" << '\n';
		std::cout << "int: impossible" << '\n';
		std::cout << "float: impossible" << '\n';
		std::cout << "double: impossible" << '\n';
		return;
	}
	print_char(value);
	print_int(value);
	print_float(value);
	print_double(value);
}
