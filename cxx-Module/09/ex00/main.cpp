#include "BitcoinExchange.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error: could not open file." << '\n';
		return 1;
	}
	try {
		BitcoinExchange exchange("data.csv");
		exchange.process_file(argv[1]);
	} catch (const std::exception& e) {
		std::cerr << e.what() << '\n';
		return 1;
	}
	return 0;
}
