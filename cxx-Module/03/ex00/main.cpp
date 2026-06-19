#include "ClapTrap.hpp"

int main(void) {
	ClapTrap clap("CL4P-TP");

	clap.attack("the bandit");
	clap.takeDamage(4);
	clap.beRepaired(2);

	for (int i = 0; i < 10; ++i) {
		clap.attack("the bandit");
	}

	return 0;
}
