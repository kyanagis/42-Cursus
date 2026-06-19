#include "WrongCat.hpp"

#include <iostream>

#include "WrongAnimal.hpp"

WrongCat::WrongCat() : WrongAnimal() {
	type_ = "WrongCat";
	std::cout << "WrongCat default constructor called" << std::endl;
}

WrongCat::WrongCat(const WrongCat& other) : WrongAnimal(other) {
	std::cout << "WrongCat copy constructor called" << std::endl;
}

WrongCat& WrongCat::operator=(const WrongCat& other) {
	std::cout << "WrongCat copy assignment operator called" << std::endl;
	WrongAnimal::operator=(other);
	return *this;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructor called" << std::endl;
}

void WrongCat::makeSound(void) const {
	std::cout << "WrongCat: Meow? (you won't see this via a WrongAnimal*)"
			  << std::endl;
}
