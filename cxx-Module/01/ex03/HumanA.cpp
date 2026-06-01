#include "HumanA.hpp"

#include <iostream>
#include <string>

#include "Weapon.hpp"

HumanA::HumanA(const std::string& name, Weapon& weapon)
	: name_(name), weapon_(weapon) {
}

HumanA::~HumanA() {
}

void HumanA::attack(void) const {
	std::cout << name_ << " attacks with their "
			  << weapon_.getType() << std::endl;
}
