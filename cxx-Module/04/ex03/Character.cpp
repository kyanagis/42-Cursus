#include "Character.hpp"

#include <string>

#include "AMateria.hpp"

Character::Character() : name_("default") {
	for (int i = 0; i < kInventorySize; ++i) {
		inventory_[i] = NULL;
	}
}

Character::Character(const std::string& name) : name_(name) {
	for (int i = 0; i < kInventorySize; ++i) {
		inventory_[i] = NULL;
	}
}

Character::Character(const Character& other)
	: ICharacter(), name_(other.name_) {
	for (int i = 0; i < kInventorySize; ++i) {
		inventory_[i] = NULL;
	}
	copyInventory(other);
}

Character& Character::operator=(const Character& other) {
	if (this != &other) {
		name_ = other.name_;
		clearInventory();
		copyInventory(other);
	}
	return *this;
}

Character::~Character() {
	clearInventory();
}

const std::string& Character::getName(void) const {
	return name_;
}

void Character::equip(AMateria* m) {
	if (m == NULL) {
		return;
	}
	for (int i = 0; i < kInventorySize; ++i) {
		if (inventory_[i] == NULL) {
			inventory_[i] = m;
			return;
		}
	}
}

void Character::unequip(int idx) {
	if (idx < 0 || idx >= kInventorySize) {
		return;
	}
	inventory_[idx] = NULL;
}

void Character::use(int idx, ICharacter& target) {
	if (idx < 0 || idx >= kInventorySize) {
		return;
	}
	if (inventory_[idx] != NULL) {
		inventory_[idx]->use(target);
	}
}

void Character::clearInventory(void) {
	for (int i = 0; i < kInventorySize; ++i) {
		delete inventory_[i];
		inventory_[i] = NULL;
	}
}

void Character::copyInventory(const Character& other) {
	for (int i = 0; i < kInventorySize; ++i) {
		if (other.inventory_[i] != NULL) {
			inventory_[i] = other.inventory_[i]->clone();
		}
	}
}
