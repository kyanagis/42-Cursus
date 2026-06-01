#include "Weapon.hpp"

#include <string>

Weapon::Weapon() : type_("") {
}

Weapon::Weapon(const std::string& type) : type_(type) {
}

Weapon::Weapon(const Weapon& other) : type_(other.type_) {
}

Weapon& Weapon::operator=(const Weapon& other) {
	if (this != &other) {
		type_ = other.type_;
	}
	return *this;
}

Weapon::~Weapon() {
}

const std::string& Weapon::getType(void) const {
	return type_;
}

void Weapon::setType(const std::string& type) {
	type_ = type;
}
