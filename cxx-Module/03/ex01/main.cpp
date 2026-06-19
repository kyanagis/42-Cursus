#include <iostream>

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main(void) {
	std::cout << "--- ClapTrap ---" << std::endl;
	ClapTrap clap("CL4P-TP");
	clap.attack("a target");

	std::cout << "--- ScavTrap ---" << std::endl;
	ScavTrap scav("SC4V-TP");
	scav.attack("a target");
	scav.takeDamage(30);
	scav.beRepaired(10);
	scav.guardGate();

	std::cout << "--- destruction (reverse order) ---" << std::endl;
	return 0;
}
