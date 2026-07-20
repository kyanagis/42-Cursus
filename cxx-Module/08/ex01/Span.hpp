#ifndef SPAN_HPP
#define SPAN_HPP

#include <cstddef>
#include <iterator>
#include <stdexcept>
#include <vector>

class Span {
public:
	Span();
	explicit Span(unsigned int maxSize);
	Span(const Span& other);
	Span& operator=(const Span& other);
	~Span();

	void addNumber(int number);
	int shortestSpan() const;
	int longestSpan() const;

	unsigned int size() const;
	unsigned int capacity() const;

	template <typename InputIt>
	void add_range(InputIt first, InputIt last) {
		std::size_t extra = std::distance(first, last);
		if (numbers_.size() + extra > maxSize_) {
			throw std::out_of_range("Span: range exceeds capacity");
		}
		numbers_.insert(numbers_.end(), first, last);
	}

	class FullException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

	class NoSpanException : public std::exception {
	public:
		virtual const char* what() const throw();
	};

private:
	unsigned int maxSize_;
	std::vector<int> numbers_;
};

#endif
