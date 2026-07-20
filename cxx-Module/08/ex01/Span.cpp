#include "Span.hpp"

#include <algorithm>
#include <limits>

Span::Span() : maxSize_(0) {
}

Span::Span(unsigned int maxSize) : maxSize_(maxSize) {
	numbers_.reserve(maxSize);
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

int Span::shortestSpan() const {
	if (numbers_.size() < 2) {
		throw NoSpanException();
	}
	std::vector<int> sorted(numbers_);
	std::sort(sorted.begin(), sorted.end());

	int shortest = std::numeric_limits<int>::max();
	for (std::size_t i = 1; i < sorted.size(); ++i) {
		int gap = sorted[i] - sorted[i - 1];
		if (gap < shortest) {
			shortest = gap;
		}
	}
	return shortest;
}

int Span::longestSpan() const {
	if (numbers_.size() < 2) {
		throw NoSpanException();
	}
	std::vector<int>::const_iterator low =
		std::min_element(numbers_.begin(), numbers_.end());
	std::vector<int>::const_iterator high =
		std::max_element(numbers_.begin(), numbers_.end());
	return *high - *low;
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
