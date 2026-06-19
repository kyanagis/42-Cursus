#include <iostream>

#include "ClapTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void) {
	std::cout << "--- ScavTrap ---" << std::endl;
	ScavTrap scav("SC4V-TP");
	scav.attack("a target");

	std::cout << "--- FragTrap ---" << std::endl;
	FragTrap frag("FR4G-TP");
	frag.attack("a target");
	frag.takeDamage(40);
	frag.beRepaired(15);
	frag.highFivesGuys();

	std::cout << "--- destruction (reverse order) ---" << std::endl;
	return 0;
}
