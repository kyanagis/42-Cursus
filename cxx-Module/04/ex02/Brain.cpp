#include "Brain.hpp"

#include <iostream>
#include <string>

Brain::Brain() {
	std::cout << "Brain default constructor called" << std::endl;
}

Brain::Brain(const Brain& other) {
	std::cout << "Brain copy constructor called" << std::endl;
	for (int i = 0; i < kIdeaCount; ++i) {
		ideas_[i] = other.ideas_[i];
	}
}

Brain& Brain::operator=(const Brain& other) {
	std::cout << "Brain copy assignment operator called" << std::endl;
	if (this != &other) {
		for (int i = 0; i < kIdeaCount; ++i) {
			ideas_[i] = other.ideas_[i];
		}
	}
	return *this;
}

Brain::~Brain() {
	std::cout << "Brain destructor called" << std::endl;
}

void Brain::setIdea(int index, const std::string& idea) {
	if (index >= 0 && index < kIdeaCount) {
		ideas_[index] = idea;
	}
}

const std::string& Brain::getIdea(int index) const {
	if (index < 0 || index >= kIdeaCount) {
		return ideas_[0];
	}
	return ideas_[index];
}
