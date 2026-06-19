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

	std::cout << "--- equip and use ---" << std::endl;
	ICharacter* me = new Character("me");
	me->equip(src->createMateria("ice"));   // slot 0
	me->equip(src->createMateria("cure"));  // slot 1
	ICharacter* bob = new Character("bob");
	me->use(0, *bob);  // * shoots an ice bolt at bob *
	me->use(1, *bob);  // * heals bob's wounds *

	std::cout << std::endl << "--- unknown type returns NULL ---" << std::endl;
	AMateria* unknown = src->createMateria("fire");
	if (unknown == NULL) {
		std::cout << "createMateria(\"fire\") -> NULL (OK)" << std::endl;
	} else {
		std::cout << "createMateria(\"fire\") -> non-NULL (BUG)" << std::endl;
		delete unknown;
	}

	std::cout << std::endl << "--- invalid use() must not crash ---"
				<< std::endl;
	me->use(-1, *bob);  // 範囲外
	me->use(99, *bob);  // 範囲外
	me->use(2, *bob);   // 空スロット
	std::cout << "survived invalid use() calls" << std::endl;

	std::cout << std::endl << "--- full inventory: 5th equip ignored ---"
				<< std::endl;
	ICharacter* greedy = new Character("greedy");
	for (int i = 0; i < 4; ++i) {
		greedy->equip(src->createMateria("ice"));  // slot 0-3 を埋める
	}
	AMateria* overflow = src->createMateria("cure");
	greedy->equip(overflow);  // 満杯 -> 格納されない
	delete overflow;          // 格納されないので呼び出し側が解放
	std::cout << "5th materia ignored, no leak" << std::endl;

	std::cout << std::endl << "--- deep copy: inventory is cloned ---"
				<< std::endl;
	{
		Character a("a");
		a.equip(src->createMateria("ice"));
		Character b(a);  // 浅いコピーなら破棄時に double free
		a.use(0, *bob);
		b.use(0, *bob);
		std::cout << "both copies use their own materia" << std::endl;
	}

	std::cout << std::endl << "--- cleanup ---" << std::endl;
	delete greedy;
	delete bob;
	delete me;
	delete src;
	return 0;
}
