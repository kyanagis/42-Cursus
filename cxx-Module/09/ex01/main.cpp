#include "RPN.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
	if (argc != 2) {
		std::cerr << "Error" << '\n';
		return 1;
	}
	try {
		RPN rpn;
		std::cout << rpn.evaluate(argv[1]) << '\n';
	} catch (const std::exception&) {
		std::cerr << "Error" << '\n';
		return 1;
	}
	return 0;
}
