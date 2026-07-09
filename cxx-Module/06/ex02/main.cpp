#include "A.hpp"
#include "B.hpp"
#include "Base.hpp"
#include "C.hpp"

#include <cstdlib>
#include <ctime>
#include <exception>
#include <iostream>

Base* generate(void) {
	int choice;

	choice = std::rand() % 3;
	if (choice == 0)
		return new A();
	if (choice == 1)
		return new B();
	return new C();
}

void identify(Base* p) {
	if (dynamic_cast<A*>(p))
		std::cout << "A" << '\n';
	else if (dynamic_cast<B*>(p))
		std::cout << "B" << '\n';
	else if (dynamic_cast<C*>(p))
		std::cout << "C" << '\n';
	else
		std::cout << "Unknown" << '\n';
}

void identify(Base& p) {
	try {
		(void)dynamic_cast<A&>(p);
		std::cout << "A" << '\n';
		return;
	} catch (std::exception&) {
	}
	try {
		(void)dynamic_cast<B&>(p);
		std::cout << "B" << '\n';
		return;
	} catch (std::exception&) {
	}
	try {
		(void)dynamic_cast<C&>(p);
		std::cout << "C" << '\n';
		return;
	} catch (std::exception&) {
	}
}

int main(void) {
	Base* p;
	int i;

	std::srand(static_cast<unsigned int>(std::time(0)));
	i = 0;
	while (i < 6) {
		p = generate();
		std::cout << "pointer   -> ";
		identify(p);
		std::cout << "reference -> ";
		identify(*p);
		std::cout << "----------" << '\n';
		delete p;
		++i;
	}
	return 0;
}
