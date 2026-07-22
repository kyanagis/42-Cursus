#include "Span.hpp"

#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

void print_head() {
	std::cout << "  slot | address        |   offset |  value\n";
	std::cout << "  -----+----------------+----------+--------\n";
}

void print_row(std::size_t slot, const int* element, const int* base,
	const char* mark) {
	std::ptrdiff_t offset;

	offset = reinterpret_cast<const char*>(element)
		- reinterpret_cast<const char*>(base);
	std::cout << "  [" << std::setw(2) << slot << "] | "
		<< std::setw(14) << element << " | "
		<< std::showpos << std::setw(8) << offset << std::noshowpos
		<< " | " << std::setw(6) << *element << mark << '\n';
}

unsigned int pair_gap(int a, int b) {
	if (a < b) {
		return static_cast<unsigned int>(b) - static_cast<unsigned int>(a);
	}
	return static_cast<unsigned int>(a) - static_cast<unsigned int>(b);
}

void mark_extremes(const std::vector<int>& values,
	std::vector<const char*>& marks) {
	std::size_t low;
	std::size_t high;
	std::size_t i;

	low = 0;
	high = 0;
	for (i = 1; i < values.size(); ++i) {
		if (values[i] < values[low]) {
			low = i;
		}
		if (values[i] > values[high]) {
			high = i;
		}
	}
	marks[low] = "  <- min : longestSpan low";
	marks[high] = "  <- max : longestSpan high";
}

void mark_closest(const std::vector<int>& values,
	std::vector<const char*>& marks) {
	std::size_t i;
	std::size_t j;
	std::size_t best_i;
	std::size_t best_j;
	unsigned int best;

	best_i = 0;
	best_j = 1;
	best = std::numeric_limits<unsigned int>::max();
	for (i = 0; i < values.size(); ++i) {
		for (j = i + 1; j < values.size(); ++j) {
			if (pair_gap(values[i], values[j]) < best) {
				best = pair_gap(values[i], values[j]);
				best_i = i;
				best_j = j;
			}
		}
	}
	if (marks[best_i][0] == '\0') {
		marks[best_i] = "  <- shortestSpan pair";
	}
	if (marks[best_j][0] == '\0') {
		marks[best_j] = "  <- shortestSpan pair";
	}
}

void span_memory_map() {
	std::vector<int> source;
	std::size_t i;

	source.push_back(17);
	source.push_back(9);
	source.push_back(91);
	source.push_back(6);
	source.push_back(42);
	source.push_back(3);
	source.push_back(88);
	source.push_back(40);

	std::vector<const char*> marks(source.size(), "");
	mark_extremes(source, marks);
	mark_closest(source, marks);

	std::cout << "=== memory map: the buffer fed to Span::addRange ===\n";
	std::cout << "  base = slot [ 0] @ " << &source[0]
		<< ", offsets in bytes (sizeof(int) = " << sizeof(int) << ")\n";
	print_head();
	for (i = 0; i < source.size(); ++i) {
		print_row(i, &source[i], &source[0], marks[i]);
	}

	Span sp(static_cast<unsigned int>(source.size()));
	sp.addRange(source.begin(), source.end());
	std::cout << "shortest: " << sp.shortestSpan()
		<< " (the two slots marked as a pair)\n";
	std::cout << "longest : " << sp.longestSpan() << " (max - min)\n";
}

void dangling_source() {
	std::vector<int> source;
	const int* freed;
	Span sp(4);

	source.push_back(10);
	source.push_back(-30);
	source.push_back(4);
	source.push_back(7);
	freed = &source[0];
	sp.addRange(source.begin(), source.end());
	std::vector<int>().swap(source);

	std::cout << "=== source buffer freed after addRange ===\n";
	std::cout << "  source base was " << freed
		<< " -> freed; reading it now = use-after-free\n";
	std::cout << "  Span still answers: shortest " << sp.shortestSpan()
		<< ", longest " << sp.longestSpan() << '\n';
	std::cout << "addRange copied the values in: the Span owns its own "
		"buffer,\nit never aliases the caller's memory\n";
}

void print_growth(std::size_t size, std::size_t capacity, const int* base,
	const char* note) {
	std::cout << "  " << std::setw(4) << size << " | " << std::setw(8)
		<< capacity << " | " << std::setw(14) << base << " |" << note << '\n';
}

void relocation_trace() {
	std::vector<int> grown;
	std::vector<int> reserved;
	const int* base;
	std::size_t i;

	std::cout << "=== buffer relocation trace: 16 push_back calls ===\n";
	std::cout << "  size | capacity |  base address  | event\n";
	std::cout << "  -----+----------+----------------+------\n";
	base = 0;
	for (i = 0; i < 16; ++i) {
		grown.push_back(static_cast<int>(i));
		if (&grown[0] != base) {
			base = &grown[0];
			print_growth(grown.size(), grown.capacity(), base,
				" realloc: old pointers now dangle");
		}
	}
	reserved.reserve(16);
	reserved.push_back(0);
	base = &reserved[0];
	for (i = 1; i < 16; ++i) {
		reserved.push_back(static_cast<int>(i));
	}
	print_growth(reserved.size(), reserved.capacity(), base,
		" reserve(16) first: base never moved");
	std::cout << "that is why Span::addRange reserves before inserting: one "
		"allocation,\nno repeated copying of the whole range\n";
}

}

int main() {
	subject_example();
	error_cases();
	extreme_values();
	canonical_form();
	range_fill();
	big_span();
	span_memory_map();
	dangling_source();
	relocation_trace();
	return 0;
}
