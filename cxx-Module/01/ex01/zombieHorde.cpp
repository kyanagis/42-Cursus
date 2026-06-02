#include <exception>
#include <iostream>
#include <string>

#include "Zombie.hpp"

Zombie* zombieHorde(int N, std::string name) {
	if (N <= 0) {
		std::cerr << "zombieHorde: N must be positive (got "
				  << N << ")" << std::endl;
		return NULL;
	}

	try {
		Zombie* horde = new Zombie[N];
		for (int i = 0; i < N; ++i) {
			horde[i].setName(name);
		}
		return horde;
	} catch (const std::exception& e) {
		std::cerr << "zombieHorde: failed to allocate " << N
				  << " zombies: " << e.what() << std::endl;
		return NULL;
	}
}
