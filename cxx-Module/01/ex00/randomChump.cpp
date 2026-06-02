#include <exception>
#include <iostream>
#include <string>

#include "Zombie.hpp"

void randomChump(const std::string& name) {
	try {
		Zombie chump(name);
		chump.announce();
	} catch (const std::exception& e) {
		std::cerr << "randomChump: failed for '" << name
					<< "': " << e.what() << '\n';
	}
}
