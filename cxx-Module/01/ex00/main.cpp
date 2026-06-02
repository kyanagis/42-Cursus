#include <iostream>

#include "Zombie.hpp"

int main(void) {
	Zombie* heapZombie = newZombie("Heap");
	if (heapZombie == NULL) {
		return 1;
	}
	heapZombie->announce();
	delete heapZombie;

	std::cout << "---" << std::endl;

	randomChump("Stack");

	return 0;
}
