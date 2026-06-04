#include <iostream>

#include "Fixed.hpp"

int main(void) {
	Fixed a;
	Fixed const b(Fixed(5.05f) * Fixed(2));

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;

	std::cout << Fixed::max(a, b) << std::endl;

	std::cout << "--- extra checks ---" << std::endl;
	Fixed const x(3);
	Fixed const y(7);
	std::cout << "x < y: " << (x < y) << std::endl;
	std::cout << "x == x: " << (x == x) << std::endl;
	std::cout << "min(x, y): " << Fixed::min(x, y) << std::endl;
	std::cout << "x + y: " << (x + y) << std::endl;
	std::cout << "y - x: " << (y - x) << std::endl;
	std::cout << "y / x: " << (y / x) << std::endl;

	return 0;
}
