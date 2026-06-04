#ifndef POINT_HPP
#define POINT_HPP

#include "Fixed.hpp"

class Point {
public:
	Point();
	Point(const float x, const float y);
	Point(const Point& other);
	Point& operator=(const Point& other);
	~Point();

	const Fixed& getX(void) const;
	const Fixed& getY(void) const;

private:
	Fixed const x_;
	Fixed const y_;
};

bool bsp(Point const a, Point const b, Point const c, Point const point);

#endif
