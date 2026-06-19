#include "FragTrap.hpp"

#include <iostream>
#include <string>

#include "ClapTrap.hpp"

FragTrap::FragTrap() : ClapTrap() {
	hitPoints_ = 100;
	energyPoints_ = 100;
	attackDamage_ = 30;
	std::cout << "FragTrap " << name_ << " constructed" << std::endl;
}

FragTrap::FragTrap(const std::string& name) : ClapTrap(name) {
	hitPoints_ = 100;
	energyPoints_ = 100;
	attackDamage_ = 30;
	std::cout << "FragTrap " << name_ << " constructed" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
	std::cout << "FragTrap " << name_ << " copied" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
	std::cout << "FragTrap " << name_ << " assigned" << std::endl;
	ClapTrap::operator=(other);
	return *this;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap " << name_ << " destroyed" << std::endl;
}

void FragTrap::highFivesGuys(void) {
	std::cout << "FragTrap " << name_
			  << " requests a positive high five! \\o/" << std::endl;
}
