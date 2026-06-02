#include "Zombie.hpp"

#include <iostream>
#include <string>

Zombie::Zombie(const std::string& name) : name_(name) {
}

Zombie::~Zombie() {
	std::cout << name_ << " is destroyed" << '\n';
}

void Zombie::announce(void) const {
	std::cout << name_ << ": BraiiiiiiinnnzzzZ..." << '\n';
}
