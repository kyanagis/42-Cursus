#include "Dog.hpp"

#include <iostream>

#include "Animal.hpp"
#include "Brain.hpp"

Dog::Dog() : Animal(), brain_(new Brain()) {
	type_ = "Dog";
	std::cout << "Dog default constructor called" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other), brain_(new Brain(*other.brain_)) {
	std::cout << "Dog copy constructor called" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
	std::cout << "Dog copy assignment operator called" << std::endl;
	if (this != &other) {
		Animal::operator=(other);
		*brain_ = *other.brain_;
	}
	return *this;
}

Dog::~Dog() {
	delete brain_;
	std::cout << "Dog destructor called" << std::endl;
}

void Dog::makeSound(void) const {
	std::cout << "Woof! Woof!" << std::endl;
}

Brain* Dog::getBrain(void) const {
	return brain_;
}
