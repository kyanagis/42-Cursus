#include "PmergeMe.hpp"

#include <exception>
#include <iostream>

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Error" << '\n';
		return 1;
	}
	try {
		PmergeMe sorter;
		sorter.run(argc, argv);
	} catch (const std::exception&) {
		std::cerr << "Error" << '\n';
		return 1;
	}
	return 0;
}
