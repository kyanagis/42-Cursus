#include "Span.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <vector>

namespace {

void subject_example() {
	std::cout << "--- subject example ---\n";
	Span sp(5);
	sp.addNumber(6);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);
	std::cout << "shortest: " << sp.shortestSpan() << '\n';
	std::cout << "longest : " << sp.longestSpan() << '\n';
}

void error_cases() {
	std::cout << "--- error cases ---\n";
	Span empty(0);
	try {
		empty.addNumber(1);
	} catch (const std::exception& e) {
		std::cout << "add to full : " << e.what() << '\n';
	}

	Span single(5);
	single.addNumber(42);
	try {
		single.shortestSpan();
	} catch (const std::exception& e) {
		std::cout << "one element : " << e.what() << '\n';
	}
	try {
		single.longestSpan();
	} catch (const std::exception& e) {
		std::cout << "one element : " << e.what() << '\n';
	}

	std::vector<int> source(3, 1);
	Span tight(2);
	try {
		tight.addRange(source.begin(), source.end());
	} catch (const std::exception& e) {
		std::cout << "range over  : " << e.what() << '\n';
	}
	std::cout << "rejected range left the Span untouched: size "
		<< tight.size() << '\n';
}

void extreme_values() {
	std::cout << "--- extreme values ---\n";
	Span sp(3);
	sp.addNumber(std::numeric_limits<int>::min());
	sp.addNumber(0);
	sp.addNumber(std::numeric_limits<int>::max());
	std::cout << "shortest: " << sp.shortestSpan() << " (2147483647)\n";
	std::cout << "longest : " << sp.longestSpan() << " (4294967295)\n";

	Span dup(3);
	dup.addNumber(7);
	dup.addNumber(-7);
	dup.addNumber(7);
	std::cout << "duplicates shortest: " << dup.shortestSpan() << " (0)\n";
}

void canonical_form() {
	std::cout << "--- copy semantics ---\n";
	Span original(5);
	original.addNumber(1);
	original.addNumber(4);

	Span copy(original);
	Span assigned;
	assigned = original;
	original.addNumber(100);

	std::cout << "original longest: " << original.longestSpan() << " (99)\n";
	std::cout << "copy     longest: " << copy.longestSpan() << " (3)\n";
	std::cout << "assigned longest: " << assigned.longestSpan() << " (3)\n";
	Span& alias = copy;
	copy = alias;
	std::cout << "self-assign size: " << copy.size() << " (2)\n";
}

void range_fill() {
	std::cout << "--- range fill ---\n";
	std::vector<int> source;
	source.push_back(5);
	source.push_back(3);
	source.push_back(-4);
	source.push_back(100);
	source.push_back(42);

	Span sp(static_cast<unsigned int>(source.size()));
	sp.addRange(source.begin(), source.end());
	std::cout << "shortest: " << sp.shortestSpan() << '\n';
	std::cout << "longest : " << sp.longestSpan() << '\n';
}

void big_span() {
	std::cout << "--- big span (20000 numbers) ---\n";
	const unsigned int count = 20000;
	Span sp(count);
	std::vector<int> source;
	source.reserve(count);
	std::srand(static_cast<unsigned int>(std::time(0)));
	for (unsigned int i = 0; i < count; ++i) {
		source.push_back(std::rand());
	}
	sp.addRange(source.begin(), source.end());
	std::cout << "size    : " << sp.size() << '\n';
	std::cout << "shortest: " << sp.shortestSpan() << '\n';
	std::cout << "longest : " << sp.longestSpan() << '\n';
}

}

int main() {
	subject_example();
	error_cases();
	extreme_values();
	canonical_form();
	range_fill();
	big_span();
	return 0;
}
