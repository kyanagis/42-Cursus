#include "Span.hpp"

#include <algorithm>
#include <limits>

namespace {

unsigned int gap_between(int low, int high) {
	return static_cast<unsigned int>(high) - static_cast<unsigned int>(low);
}

}

Span::Span() : maxSize_(0) {
}

Span::Span(unsigned int maxSize) : maxSize_(maxSize) {
}

Span::Span(const Span& other)
	: maxSize_(other.maxSize_), numbers_(other.numbers_) {
}

Span& Span::operator=(const Span& other) {
	if (this != &other) {
		maxSize_ = other.maxSize_;
		numbers_ = other.numbers_;
	}
	return *this;
}

Span::~Span() {
}

void Span::addNumber(int number) {
	if (numbers_.size() >= maxSize_) {
		throw FullException();
	}
	numbers_.push_back(number);
}

unsigned int Span::shortestSpan() const {
	if (numbers_.size() < 2) {
		throw NoSpanException();
	}
	std::vector<int> sorted(numbers_);
	std::sort(sorted.begin(), sorted.end());

	unsigned int shortest = std::numeric_limits<unsigned int>::max();
	for (std::size_t i = 1; i < sorted.size(); ++i) {
		unsigned int gap = gap_between(sorted[i - 1], sorted[i]);
		if (gap == 0) {
			return 0;
		}
		if (gap < shortest) {
			shortest = gap;
		}
	}
	return shortest;
}

unsigned int Span::longestSpan() const {
	if (numbers_.size() < 2) {
		throw NoSpanException();
	}
	std::vector<int>::const_iterator low =
		std::min_element(numbers_.begin(), numbers_.end());
	std::vector<int>::const_iterator high =
		std::max_element(numbers_.begin(), numbers_.end());
	return gap_between(*low, *high);
}

unsigned int Span::size() const {
	return static_cast<unsigned int>(numbers_.size());
}

unsigned int Span::capacity() const {
	return maxSize_;
}

const char* Span::FullException::what() const throw() {
	return "Span: cannot add to a full Span";
}

const char* Span::NoSpanException::what() const throw() {
	return "Span: no span can be found";
}
