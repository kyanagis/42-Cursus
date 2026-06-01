#include "HumanB.hpp"

#include <iostream>
#include <string>

#include "Weapon.hpp"

HumanB::HumanB(const std::string& name) : name_(name), weapon_(NULL) {
}

HumanB::~HumanB() {
}

void HumanB::setWeapon(Weapon& weapon) {
	weapon_ = &weapon;
}

void HumanB::attack(void) const {
	if (weapon_ == NULL) {
		std::cout << name_ << " has no weapon to attack with" << std::endl;
		return;
	}
	std::cout << name_ << " attacks with their "
			  << weapon_->getType() << std::endl;
}
