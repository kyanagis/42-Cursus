#include <iostream>

#include "Bureaucrat.hpp"

int main(void) {
	std::cout << "=== Valid bureaucrat ===" << '\n';
	try {
		Bureaucrat alice("Alice", 3);
		std::cout << alice << '\n';
		alice.incrementGrade();
		std::cout << "after increment: " << alice << '\n';
		alice.decrementGrade();
		alice.decrementGrade();
		std::cout << "after two decrements: " << alice << '\n';
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\n=== Grade too high at construction ===" << '\n';
	try {
		Bureaucrat bob("Bob", 0);
		std::cout << bob << '\n';
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\n=== Grade too low at construction ===" << '\n';
	try {
		Bureaucrat carol("Carol", 151);
		std::cout << carol << '\n';
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\n=== Increment past the highest grade ===" << '\n';
	try {
		Bureaucrat dave("Dave", 1);
		std::cout << dave << '\n';
		dave.incrementGrade();
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	std::cout << "\n=== Decrement past the lowest grade ===" << '\n';
	try {
		Bureaucrat eve("Eve", 150);
		std::cout << eve << '\n';
		eve.decrementGrade();
	} catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << '\n';
	}

	return 0;
}
