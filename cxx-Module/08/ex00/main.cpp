#include "easyfind.hpp"

#include <iostream>
#include <list>
#include <vector>

static void search_vector(std::vector<int>& numbers, int value) {
	std::cout << "vector: searching for " << value << " -> ";
	try {
		std::vector<int>::iterator it = easyfind(numbers, value);
		std::cout << "found (index " << (it - numbers.begin()) << ")\n";
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

static void search_list(const std::list<int>& numbers, int value) {
	std::cout << "list  : searching for " << value << " -> ";
	try {
		std::list<int>::const_iterator it = easyfind(numbers, value);
		std::cout << "found (" << *it << ")\n";
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

int main() {
	std::vector<int> numbers;
	for (int i = 0; i < 10; ++i) {
		numbers.push_back(i * 2);
	}

	search_vector(numbers, 8);
	search_vector(numbers, 0);
	search_vector(numbers, 18);
	search_vector(numbers, 7);
	search_vector(numbers, -1);

	std::list<int> letters;
	letters.push_back(42);
	letters.push_back(21);
	letters.push_back(84);
	search_list(letters, 21);
	search_list(letters, 100);

	std::vector<int> empty;
	search_vector(empty, 1);

	return 0;
}
