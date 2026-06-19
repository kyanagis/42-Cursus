#include "ScavTrap.hpp"

#include <iostream>
#include <string>

#include "ClapTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap() {
	hitPoints_ = 100;
	energyPoints_ = 50;
	attackDamage_ = 20;
	std::cout << "ScavTrap " << name_ << " constructed" << std::endl;
}

ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
	hitPoints_ = 100;
	energyPoints_ = 50;
	attackDamage_ = 20;
	std::cout << "ScavTrap " << name_ << " constructed" << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap& other) : ClapTrap(other) {
	std::cout << "ScavTrap " << name_ << " copied" << std::endl;
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other) {
	std::cout << "ScavTrap " << name_ << " assigned" << std::endl;
	ClapTrap::operator=(other);
	return *this;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap " << name_ << " destroyed" << std::endl;
}

void ScavTrap::attack(const std::string& target) {
	if (hitPoints_ == 0 || energyPoints_ == 0) {
		std::cout << "ScavTrap " << name_
				  << " cannot attack (out of hit or energy points)"
				  << std::endl;
		return;
	}
	--energyPoints_;
	std::cout << "ScavTrap " << name_ << " bites " << target
			  << ", causing " << attackDamage_ << " points of damage!"
			  << std::endl;
}

void ScavTrap::guardGate(void) {
	std::cout << "ScavTrap " << name_ << " is now in Gate keeper mode"
			  << std::endl;
}
