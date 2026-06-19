#include <iostream>
#include <string>

#include "Animal.hpp"
#include "Brain.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main(void) {
	const int kSize = 4;
	const Animal* animals[kSize];

	for (int i = 0; i < kSize / 2; ++i) {
		animals[i] = new Dog();
	}
	for (int i = kSize / 2; i < kSize; ++i) {
		animals[i] = new Cat();
	}

	std::cout << std::endl << "--- sounds ---" << std::endl;
	for (int i = 0; i < kSize; ++i) {
		animals[i]->makeSound();
	}

	std::cout << std::endl << "--- delete as Animal* ---" << std::endl;
	for (int i = 0; i < kSize; ++i) {
		delete animals[i];
	}

	std::cout << std::endl << "=== deep copy test ===" << std::endl;
	{
		Dog original;
		original.getBrain()->setIdea(0, "I want a bone");

		Dog copy(original);
		copy.getBrain()->setIdea(0, "I want a different bone");

		std::cout << "original idea 0: "
				  << original.getBrain()->getIdea(0) << std::endl;
		std::cout << "copy idea 0:     "
				  << copy.getBrain()->getIdea(0) << std::endl;

		std::string same = "no";
		if (original.getBrain() != copy.getBrain()) {
			same = "yes";
		}
		std::cout << "different Brain addresses: " << same << std::endl;
	}

	return 0;
}
