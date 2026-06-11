#include "Fixed.hpp"

#include <cmath>

#include <iostream>

Fixed::Fixed() : value_(0) {
	std::cout << "Default constructor called" << '\n';
}

Fixed::Fixed(const int value) : value_(value << kFractionalBits) {
	std::cout << "Int constructor called" << '\n';
}

Fixed::Fixed(const float value)
	: value_(static_cast<int>(roundf(value * (1 << kFractionalBits)))) {
	std::cout << "Float constructor called" << '\n';
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
	return value_;
}

void Fixed::setRawBits(int const raw) {
	value_ = raw;
}

float Fixed::toFloat(void) const {
	return static_cast<float>(value_) / (1 << kFractionalBits);
}

int Fixed::toInt(void) const {
	return value_ >> kFractionalBits;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
	out << fixed.toFloat();
	return out;
}
