#include <exception>
#include <iostream>
#include <string>

#include "Zombie.hpp"

Zombie* newZombie(std::string name) {
	try {
		return new Zombie(name);
	} catch (const std::exception& e) {
		std::cerr << "newZombie: failed to allocate '" << name
				  << "': " << e.what() << std::endl;
		return NULL;
	}
}
