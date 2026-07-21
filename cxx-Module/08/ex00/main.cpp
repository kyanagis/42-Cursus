#include "easyfind.hpp"

#include <cstddef>
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

static void print_vector_addresses(const std::vector<int>& numbers) {
	for (std::size_t i = 0; i < numbers.size(); ++i) {
		std::cout << "  " << numbers[i] << " @ " << &numbers[i] << '\n';
	}
}

static void print_list_addresses(const std::list<int>& numbers) {
	std::list<int>::const_iterator it;
	for (it = numbers.begin(); it != numbers.end(); ++it) {
		std::cout << "  " << *it << " @ " << &*it << '\n';
	}
}

static void reuse_freed_node(std::list<int>& numbers) {
	std::list<int>::iterator it;

	numbers.push_front(-1);
	it = numbers.begin();
	++it;
	++it;
	numbers.erase(it);
	numbers.push_back(99);
}

static void show_memory_layout() {
	std::vector<int> contiguous;
	std::list<int> nodes;

	for (int i = 0; i < 5; ++i) {
		contiguous.push_back(i);
		nodes.push_back(i);
	}
	std::cout << "--- vector: address == base + index * sizeof(int) ---\n";
	print_vector_addresses(contiguous);
	std::cout << "--- list: independently allocated nodes ---\n";
	print_list_addresses(nodes);
	reuse_freed_node(nodes);
	std::cout << "--- list: after erase and push_back ---\n";
	print_list_addresses(nodes);
	std::cout << "traversal order no longer follows address order\n";
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

	show_memory_layout();

	return 0;
}
