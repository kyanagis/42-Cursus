#include <iostream>

#include "Zombie.hpp"

int main(void) {
	const int kCount = 5;
	Zombie* horde = zombieHorde(kCount, "Horde");

	if (horde == NULL) {
		std::cout << "zombieHorde returned NULL" << std::endl;
		return 1;
	}

	for (int i = 0; i < kCount; ++i) {
		horde[i].announce();
	}

	delete[] horde;
	return 0;
}
