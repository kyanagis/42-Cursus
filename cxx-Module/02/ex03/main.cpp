#include <iostream>
#include <string>

#include "Point.hpp"

static std::string side(bool inside) {
	if (inside) {
		return "inside";
	}
	return "outside";
}

static void check(const char* label, bool actual, bool expected) {
	std::string verdict = "[OK]";
	if (actual != expected) {
		verdict = "[FAIL]";
	}
	std::cout << label << ": " << side(actual)
				<< " (expected " << side(expected) << ") " << verdict
				<< std::endl;
}

int main(void) {
	Point const a(0.0f, 0.0f);
	Point const b(10.0f, 0.0f);
	Point const c(0.0f, 10.0f);

	check("interior (2,2)", bsp(a, b, c, Point(2.0f, 2.0f)), true);
	check("centroid-ish (3,3)", bsp(a, b, c, Point(3.0f, 3.0f)), true);
	check("on edge (5,0)", bsp(a, b, c, Point(5.0f, 0.0f)), false);
	check("on vertex (0,0)", bsp(a, b, c, Point(0.0f, 0.0f)), false);
	check("outside (10,10)", bsp(a, b, c, Point(10.0f, 10.0f)), false);
	check("outside (-1,-1)", bsp(a, b, c, Point(-1.0f, -1.0f)), false);

	return 0;
}
