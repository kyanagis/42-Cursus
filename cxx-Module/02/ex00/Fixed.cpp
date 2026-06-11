#include "Fixed.hpp"

#include <iostream>

Fixed::Fixed() : value_(0) {
	std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const Fixed& other) : value_(other.value_) {
	std::cout << "Copy constructor called" << '\n';
}

Fixed& Fixed::operator=(const Fixed& other) {
	std::cout << "Copy assignment operator called" << '\n';
	if (this != &other) {
		value_ = other.value_;
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << '\n';
}

int Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << '\n';
	return value_;
}

void Fixed::setRawBits(int const raw) {
	value_ = raw;
}
