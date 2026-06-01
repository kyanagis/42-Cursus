#include <iostream>

#include "Zombie.hpp"

int main(void) {
	Zombie* heapZombie = newZombie("Heap");
	heapZombie->announce();
	delete heapZombie;

	std::cout << "---" << std::endl;

	randomChump("Stack");

	return 0;
}
