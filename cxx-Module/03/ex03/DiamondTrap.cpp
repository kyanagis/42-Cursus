#include "DiamondTrap.hpp"

#include <iostream>
#include <string>

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

DiamondTrap::DiamondTrap()
	: ClapTrap("default_clap_name"), FragTrap(), ScavTrap(), name_("default") {
	energyPoints_ = 50;
	attackDamage_ = 30;
	std::cout << "DiamondTrap " << name_ << " constructed" << std::endl;
}

DiamondTrap::DiamondTrap(const std::string& name)
	: ClapTrap(name + "_clap_name"), FragTrap(name), ScavTrap(name),
	  name_(name) {
	energyPoints_ = 50;
	attackDamage_ = 30;
	std::cout << "DiamondTrap " << name_ << " constructed" << std::endl;
}

DiamondTrap::DiamondTrap(const DiamondTrap& other)
	: ClapTrap(other), FragTrap(other), ScavTrap(other), name_(other.name_) {
	std::cout << "DiamondTrap " << name_ << " copied" << std::endl;
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other) {
	std::cout << "DiamondTrap " << name_ << " assigned" << std::endl;
	if (this != &other) {
		ClapTrap::operator=(other);
		name_ = other.name_;
	}
	return *this;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap " << name_ << " destroyed" << std::endl;
}

void DiamondTrap::whoAmI(void) {
	std::cout << "DiamondTrap name: " << name_
			  << " | ClapTrap name: " << ClapTrap::name_ << std::endl;
}
