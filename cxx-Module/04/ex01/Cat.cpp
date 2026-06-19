#include "Cat.hpp"

#include <iostream>

#include "Animal.hpp"
#include "Brain.hpp"

Cat::Cat() : Animal(), brain_(new Brain()) {
	type_ = "Cat";
	std::cout << "Cat default constructor called" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other), brain_(new Brain(*other.brain_)) {
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		*brain_ = *other.brain_;
	}
	return *this;
}

Cat::~Cat() {
	delete brain_;
	std::cout << "Cat destructor called" << std::endl;
}

void Cat::makeSound(void) const {
	std::cout << "Meow! Meow!" << std::endl;
}

Brain* Cat::getBrain(void) const {
	return brain_;
}
