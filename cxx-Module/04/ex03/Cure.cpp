#include "Cure.hpp"

#include <iostream>

#include "AMateria.hpp"
#include "ICharacter.hpp"

Cure::Cure() : AMateria("cure") {
}

Cure::Cure(const Cure& other) : AMateria(other) {
	type_ = "cure";
}

Cure& Cure::operator=(const Cure& other) {
	AMateria::operator=(other);
	return *this;
}

Cure::~Cure() {
}

AMateria* Cure::clone(void) const {
	return new Cure(*this);
}

void Cure::use(ICharacter& target) {
	std::cout << "* heals " << target.getName() << "'s wounds *" << std::endl;
}
