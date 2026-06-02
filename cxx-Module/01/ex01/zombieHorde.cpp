#include <exception>
#include <iostream>
#include <string>

#include "Zombie.hpp"

Zombie* zombieHorde(int N, const std::string& name) {
	if (N <= 0) {
		std::cerr << "zombieHorde: N must be positive (got "
					<< N << ")" << '\n';
		return NULL;
	}

	try {
		Zombie* horde = new Zombie[N];
		for (int i = 0; i < N; ++i) {
			horde[i].set_name(name);
		}
		return horde;
	} catch (const std::exception& e) {
		std::cerr << "zombieHorde: failed to allocate " << N
					<< " zombies: " << e.what() << '\n';
		return NULL;
	}
}
