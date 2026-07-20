#include "Span.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

static void subject_example() {
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

static void error_cases() {
	std::cout << "--- error cases ---\n";
	Span empty(0);
	try {
		empty.addNumber(1);
	} catch (const std::exception& e) {
		std::cout << "add to full: " << e.what() << '\n';
	}

	Span single(5);
	single.addNumber(42);
	try {
		single.shortestSpan();
	} catch (const std::exception& e) {
		std::cout << "one element: " << e.what() << '\n';
	}
}

static void range_fill() {
	std::cout << "--- range fill ---\n";
	std::vector<int> source;
	source.push_back(5);
	source.push_back(3);
	source.push_back(-4);
	source.push_back(100);
	source.push_back(42);

	Span sp(source.size());
	sp.add_range(source.begin(), source.end());
	std::cout << "shortest: " << sp.shortestSpan() << '\n';
	std::cout << "longest : " << sp.longestSpan() << '\n';
}

static void big_span() {
	std::cout << "--- big span (20000 numbers) ---\n";
	const unsigned int count = 20000;
	Span sp(count);
	std::vector<int> source;
	source.reserve(count);
	std::srand(static_cast<unsigned int>(std::time(0)));
	for (unsigned int i = 0; i < count; ++i) {
		source.push_back(std::rand());
	}
	sp.add_range(source.begin(), source.end());
	std::cout << "size    : " << sp.size() << '\n';
	std::cout << "shortest: " << sp.shortestSpan() << '\n';
	std::cout << "longest : " << sp.longestSpan() << '\n';
}

int main() {
	subject_example();
	error_cases();
	range_fill();
	big_span();
	return 0;
}
