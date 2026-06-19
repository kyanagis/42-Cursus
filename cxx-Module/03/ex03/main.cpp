#include <iostream>

#include "ClapTrap.hpp"
#include "DiamondTrap.hpp"
#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main(void) {
	std::cout << "--- construct DiamondTrap ---" << std::endl;
	DiamondTrap diamond("Dia");

	std::cout << "--- whoAmI ---" << std::endl;
	diamond.whoAmI();

	std::cout << "--- actions ---" << std::endl;
	diamond.attack("a target");
	diamond.takeDamage(30);
	diamond.beRepaired(10);
	diamond.guardGate();
	diamond.highFivesGuys();

	std::cout << "--- destruction (reverse order) ---" << std::endl;
	return 0;
}
