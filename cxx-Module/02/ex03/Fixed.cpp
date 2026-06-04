#include "Fixed.hpp"

#include <cmath>

#include <iostream>

Fixed::Fixed() : value_(0) {
}

Fixed::Fixed(const int value) : value_(value << kFractionalBits) {
}

Fixed::Fixed(const float value)
	: value_(static_cast<int>(roundf(value * (1 << kFractionalBits)))) {
}

Fixed::Fixed(const Fixed& other) : value_(other.value_) {
}

Fixed& Fixed::operator=(const Fixed& other) {
	if (this != &other) {
		value_ = other.value_;
	}
	return *this;
}

Fixed::~Fixed() {
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

bool Fixed::operator>(const Fixed& rhs) const {
	return value_ > rhs.value_;
}

bool Fixed::operator<(const Fixed& rhs) const {
	return value_ < rhs.value_;
}

bool Fixed::operator>=(const Fixed& rhs) const {
	return value_ >= rhs.value_;
}

bool Fixed::operator<=(const Fixed& rhs) const {
	return value_ <= rhs.value_;
}

bool Fixed::operator==(const Fixed& rhs) const {
	return value_ == rhs.value_;
}

bool Fixed::operator!=(const Fixed& rhs) const {
	return value_ != rhs.value_;
}

Fixed Fixed::operator+(const Fixed& rhs) const {
	Fixed result;
	result.setRawBits(value_ + rhs.value_);
	return result;
}

Fixed Fixed::operator-(const Fixed& rhs) const {
	Fixed result;
	result.setRawBits(value_ - rhs.value_);
	return result;
}

Fixed Fixed::operator*(const Fixed& rhs) const {
	Fixed result;
	long product = static_cast<long>(value_) * rhs.value_;
	result.setRawBits(static_cast<int>(product >> kFractionalBits));
	return result;
}

Fixed Fixed::operator/(const Fixed& rhs) const {
	Fixed result;
	long numerator = static_cast<long>(value_) << kFractionalBits;
	result.setRawBits(static_cast<int>(numerator / rhs.value_));
	return result;
}

Fixed& Fixed::operator++() {
	++value_;
	return *this;
}

Fixed Fixed::operator++(int) {
	Fixed before(*this);
	++value_;
	return before;
}

Fixed& Fixed::operator--() {
	--value_;
	return *this;
}

Fixed Fixed::operator--(int) {
	Fixed before(*this);
	--value_;
	return before;
}

Fixed& Fixed::min(Fixed& a, Fixed& b) {
	if (a < b) {
		return a;
	}
	return b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b) {
	if (a < b) {
		return a;
	}
	return b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b) {
	if (a > b) {
		return a;
	}
	return b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b) {
	if (a > b) {
		return a;
	}
	return b;
}

std::ostream& operator<<(std::ostream& out, const Fixed& fixed) {
	out << fixed.toFloat();
	return out;
}
