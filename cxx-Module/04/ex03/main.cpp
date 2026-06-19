#include <iostream>

#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"

int main(void) {
	IMateriaSource* src = new MateriaSource();
	src->learnMateria(new Ice());
	src->learnMateria(new Cure());

	ICharacter* me = new Character("me");

	AMateria* tmp;
	tmp = src->createMateria("ice");
	me->equip(tmp);
	tmp = src->createMateria("cure");
	me->equip(tmp);

	ICharacter* bob = new Character("bob");

	me->use(0, *bob);
	me->use(1, *bob);

	AMateria* unknown = src->createMateria("fire");
	if (unknown == NULL) {
		std::cout << "createMateria(\"fire\") -> NULL (as expected)"
				  << std::endl;
	} else {
		std::cout << "createMateria(\"fire\") -> non-NULL (unexpected)"
				  << std::endl;
		delete unknown;
	}

	delete bob;
	delete me;
	delete src;

	return 0;
}
