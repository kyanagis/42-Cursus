#include <iostream>

#include "Bureaucrat.hpp"
#include "Form.hpp"

int main(void) {
	std::cout << "=== Invalid form grades ===" << '\n';
	try {
		Form bad("bad", 0, 10);
		std::cout << bad << '\n';
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\n=== High-grade bureaucrat signs successfully ===" << '\n';
	try {
		Bureaucrat boss("Boss", 1);
		Form contract("contract", 50, 25);
		std::cout << contract << '\n';
		boss.signForm(contract);
		std::cout << contract << '\n';
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\n=== Low-grade bureaucrat fails to sign ===" << '\n';
	try {
		Bureaucrat rookie("Rookie", 100);
		Form contract("contract", 50, 25);
		rookie.signForm(contract);
		std::cout << contract << '\n';
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\n=== beSigned throws directly ===" << '\n';
	try {
		Bureaucrat rookie("Rookie", 100);
		Form contract("contract", 50, 25);
		contract.beSigned(rookie);
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	return 0;
}
