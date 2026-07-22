#include "easyfind.hpp"

#include <cstddef>
#include <iomanip>
#include <iostream>
#include <list>
#include <vector>

namespace {

void search_vector(std::vector<int>& numbers, int value) {
	std::cout << "vector: searching for " << value << " -> ";
	try {
		std::vector<int>::iterator it = easyfind(numbers, value);
		std::cout << "found (index " << (it - numbers.begin()) << ")\n";
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void search_list(const std::list<int>& numbers, int value) {
	std::cout << "list  : searching for " << value << " -> ";
	try {
		std::list<int>::const_iterator it = easyfind(numbers, value);
		std::cout << "found (" << *it << ")\n";
	} catch (const std::exception& e) {
		std::cout << e.what() << '\n';
	}
}

void print_entry(std::size_t index, const int* element,
	const int* base) {
	std::ptrdiff_t offset;

	offset = reinterpret_cast<const char*>(element)
		- reinterpret_cast<const char*>(base);
	std::cout << "  [" << index << "] value " << std::setw(3) << *element
		<< " @ " << element
		<< "  offset " << std::showpos << std::setw(8) << offset
		<< std::noshowpos << " bytes\n";
}

void print_vector_addresses(const std::vector<int>& numbers) {
	if (numbers.empty()) {
		return;
	}
	for (std::size_t i = 0; i < numbers.size(); ++i) {
		print_entry(i, &numbers[i], &numbers[0]);
	}
}

void print_list_addresses(const std::list<int>& numbers) {
	std::list<int>::const_iterator it;
	std::size_t i;

	if (numbers.empty()) {
		return;
	}
	i = 0;
	for (it = numbers.begin(); it != numbers.end(); ++it) {
		print_entry(i, &*it, &*numbers.begin());
		++i;
	}
}

void reuse_freed_node(std::list<int>& numbers) {
	std::list<int>::iterator it;

	numbers.push_front(-1);
	it = numbers.begin();
	++it;
	++it;
	numbers.erase(it);
	numbers.push_back(99);
}

void show_memory_layout() {
	std::vector<int> contiguous;
	std::list<int> nodes;

	for (int i = 0; i < 5; ++i) {
		contiguous.push_back(i);
		nodes.push_back(i);
	}
	std::cout << "offset = bytes from the first element (sizeof(int) = "
		<< sizeof(int) << ")\n";
	std::cout << "--- vector: address == base + index * sizeof(int) ---\n";
	print_vector_addresses(contiguous);
	std::cout << "offset grows by exactly " << sizeof(int)
		<< " each step: one contiguous block\n";
	std::cout << "--- list: independently allocated nodes ---\n";
	print_list_addresses(nodes);
	std::cout << "offset jumps by arbitrary amounts: one node per element\n";
	reuse_freed_node(nodes);
	std::cout << "--- list: after erase and push_back ---\n";
	print_list_addresses(nodes);
	std::cout << "offset can even go negative: traversal order no longer "
		"follows address order\n";
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

	show_memory_layout();

	return 0;
}
