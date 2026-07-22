#ifndef SPAN_HPP
#define SPAN_HPP

#include <cstddef>
#include <exception>
#include <iterator>
#include <vector>

class Span {
public:
	Span();
	explicit Span(unsigned int maxSize);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void addNumber(int number);
	unsigned int shortestSpan() const;
	unsigned int longestSpan() const;

	unsigned int size() const;
	unsigned int capacity() const;

	class FullException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class NoSpanException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	template <typename ForwardIt>
	void addRange(ForwardIt first, ForwardIt last) {
		std::ptrdiff_t extra = std::distance(first, last);

		if (extra < 0 || static_cast<std::size_t>(extra)
				> maxSize_ - numbers_.size()) {
			throw FullException();
		}
		numbers_.reserve(numbers_.size() + static_cast<std::size_t>(extra));
		numbers_.insert(numbers_.end(), first, last);
	}

private:
	unsigned int maxSize_;
	std::vector<int> numbers_;
};

#endif
