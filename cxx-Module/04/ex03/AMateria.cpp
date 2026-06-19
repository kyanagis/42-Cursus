#include "AMateria.hpp"

#include <iostream>
#include <string>

AMateria::AMateria() : type_("") {
}

AMateria::AMateria(const std::string& type) : type_(type) {
}

AMateria::AMateria(const AMateria& other) : type_(other.type_) {
}

AMateria& AMateria::operator=(const AMateria& other) {
	(void)other;
	return *this;
}

AMateria::~AMateria() {
}

const std::string& AMateria::getType(void) const {
	return type_;
}

void AMateria::use(ICharacter& target) {
	(void)target;
}
