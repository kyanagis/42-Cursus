#include "Zombie.hpp"

#include <iostream>
#include <string>

Zombie::Zombie() : name_("no name") {
}

Zombie::~Zombie() {
	std::cout << name_ << " is destroyed" << std::endl;
}

void Zombie::announce(void) const {
	std::cout << name_ << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(const std::string& name) {
	name_ = name;
}
