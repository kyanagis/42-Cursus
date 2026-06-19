#include "Animal.hpp"

#include <iostream>
#include <string>

Animal::Animal() : type_("Animal") {
	std::cout << "Animal default constructor called" << std::endl;
}

Animal::Animal(const Animal& other) : type_(other.type_) {
	std::cout << "Animal copy constructor called" << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
	std::cout << "Animal copy assignment operator called" << std::endl;
	if (this != &other) {
		type_ = other.type_;
	}
	return *this;
}

Animal::~Animal() {
	std::cout << "Animal destructor called" << std::endl;
}

void Animal::makeSound(void) const {
	std::cout << "* some generic animal sound *" << std::endl;
}

const std::string& Animal::getType(void) const {
	return type_;
}
