#include <exception>
#include <iostream>
#include <string>

#include "Zombie.hpp"

void randomChump(std::string name) {
	try {
		Zombie chump(name);
		chump.announce();
	} catch (const std::exception& e) {
		std::cerr << "randomChump: failed for '" << name
				  << "': " << e.what() << std::endl;
	}
}
