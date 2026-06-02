#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

static void armed_human_a(void) {
	Weapon club = Weapon("crude spiked club");
	HumanA bob("Bob", club);

	bob.attack();
	club.setType("some other type of club");
	bob.attack();
}

static void armed_human_b(void) {
	Weapon club = Weapon("crude spiked club");
	HumanB jim("Jim");

	jim.setWeapon(club);
	jim.attack();
	club.setType("some other type of club");
	jim.attack();
}

static void unarmed_human_b(void) {
	HumanB ghost("Ghost");

	ghost.attack();
}

int main(void) {
	armed_human_a();
	armed_human_b();
	unarmed_human_b();

	return 0;
}
