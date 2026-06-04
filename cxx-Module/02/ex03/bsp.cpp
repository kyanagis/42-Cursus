#include "Fixed.hpp"
#include "Point.hpp"

static Fixed signedArea2(const Point& a, const Point& b, const Point& c) {
	return (b.getX() - a.getX()) * (c.getY() - a.getY())
			- (b.getY() - a.getY()) * (c.getX() - a.getX());
}

bool bsp(Point const a, Point const b, Point const c, Point const point) {
	Fixed const zero(0);

	Fixed d1 = signedArea2(a, b, point);
	Fixed d2 = signedArea2(b, c, point);
	Fixed d3 = signedArea2(c, a, point);

	if (d1 == zero || d2 == zero || d3 == zero) {
		return false;
	}

	bool hasNegative = (d1 < zero) || (d2 < zero) || (d3 < zero);
	bool hasPositive = (d1 > zero) || (d2 > zero) || (d3 > zero);

	return !(hasNegative && hasPositive);
}
