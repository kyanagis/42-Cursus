#include "ClapTrap.hpp"

#include <iostream>
#include <string>

ClapTrap::ClapTrap()
	: name_("default"), hitPoints_(10), energyPoints_(10), attackDamage_(0) {
	std::cout << "ClapTrap " << name_ << " constructed" << std::endl;
}

ClapTrap::ClapTrap(const std::string& name)
	: name_(name), hitPoints_(10), energyPoints_(10), attackDamage_(0) {
	std::cout << "ClapTrap " << name_ << " constructed" << std::endl;
}

ClapTrap::ClapTrap(const ClapTrap& other)
	: name_(other.name_), hitPoints_(other.hitPoints_),
	  energyPoints_(other.energyPoints_), attackDamage_(other.attackDamage_) {
	std::cout << "ClapTrap " << name_ << " copied" << std::endl;
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other) {
	std::cout << "ClapTrap " << name_ << " assigned" << std::endl;
	if (this != &other) {
		name_ = other.name_;
		hitPoints_ = other.hitPoints_;
		energyPoints_ = other.energyPoints_;
		attackDamage_ = other.attackDamage_;
	}
	return *this;
}

ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap " << name_ << " destroyed" << std::endl;
}

void ClapTrap::attack(const std::string& target) {
	if (hitPoints_ == 0 || energyPoints_ == 0) {
		std::cout << "ClapTrap " << name_
				  << " cannot attack (out of hit or energy points)"
				  << std::endl;
		return;
	}
	--energyPoints_;
	std::cout << "ClapTrap " << name_ << " attacks " << target
			  << ", causing " << attackDamage_ << " points of damage!"
			  << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount) {
	if (amount >= hitPoints_) {
		hitPoints_ = 0;
	} else {
		hitPoints_ -= amount;
	}
	std::cout << "ClapTrap " << name_ << " takes " << amount
			  << " points of damage! (" << hitPoints_ << " HP left)"
			  << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount) {
	if (hitPoints_ == 0 || energyPoints_ == 0) {
		std::cout << "ClapTrap " << name_
				  << " cannot repair (out of hit or energy points)"
				  << std::endl;
		return;
	}
	--energyPoints_;
	hitPoints_ += amount;
	std::cout << "ClapTrap " << name_ << " repairs itself for " << amount
			  << " hit points! (" << hitPoints_ << " HP)" << std::endl;
}
