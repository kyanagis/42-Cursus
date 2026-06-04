#include "Point.hpp"

#include "Fixed.hpp"

Point::Point() : x_(0), y_(0) {
}

Point::Point(const float x, const float y) : x_(x), y_(y) {
}

Point::Point(const Point& other) : x_(other.x_), y_(other.y_) {
}

Point& Point::operator=(const Point& other) {
	(void)other;
	return *this;
}

Point::~Point() {
}

const Fixed& Point::getX(void) const {
	return x_;
}

const Fixed& Point::getY(void) const {
	return y_;
}
