#include "Zombie.hpp"

#include <iostream>
#include <string>

Zombie::Zombie() : name_("no name") {
}

Zombie::~Zombie() {
	std::cout << name_ << " is destroyed" << '\n';
}

void Zombie::announce(void) const {
	std::cout << name_ << ": BraiiiiiiinnnzzzZ..." << '\n';
}

void Zombie::set_name(const std::string& name) {
	name_ = name;
}
