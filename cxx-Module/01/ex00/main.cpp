#include <iostream>

#include "Zombie.hpp"

static int heap_zombie(void) {
	Zombie* zombie = newZombie("Heap");
	if (zombie == NULL) {
		return 1;
	}
	zombie->announce();
	delete zombie;
	return 0;
}

int main(void) {
	if (heap_zombie() != 0) {
		return 1;
	}
	std::cout << "---" << '\n';
	randomChump("Stack");
	return 0;
}
