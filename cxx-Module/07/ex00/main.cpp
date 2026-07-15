#include "whatever.hpp"
#include <iostream>
#include <string>

int main(void)
{
	int a = 2;
	int b = 3;

	::swap(a, b);
	std::cout << "a = " << a << ", b = " << b << std::endl;
	std::cout << "min( a, b ) = " << ::min(a, b) << std::endl;
	std::cout << "max( a, b ) = " << ::max(a, b) << std::endl;

	std::string c = "chaine1";
	std::string d = "chaine2";

	::swap(c, d);
	std::cout << "c = " << c << ", d = " << d << std::endl;
	std::cout << "min( c, d ) = " << ::min(c, d) << std::endl;
	std::cout << "max( c, d ) = " << ::max(c, d) << std::endl;

	int e = 5;
	int f = 5;
	bool min_is_second = (&::min(e, f) == &f);
	bool max_is_second = (&::max(e, f) == &f);

	std::cout << "min of equal -> 2nd: " << min_is_second << std::endl;
	std::cout << "max of equal -> 2nd: " << max_is_second << std::endl;

	return 0;
}
