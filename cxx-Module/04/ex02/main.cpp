#include <iostream>
#include <string>

#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"

int main(void) {
	std::cout << "--- abstract class cannot be instantiated ---" << std::endl;
	// const AAnimal* impossible = new AAnimal();
	//   ↑ AAnimal は純粋仮想 makeSound() を持つ抽象クラスなので、
	//     この行はコンパイルエラーになる。これが ex02 の要点。
	std::cout << "new AAnimal() does not compile (see comment)" << std::endl;

	std::cout << std::endl << "--- polymorphism via AAnimal* ---" << std::endl;
	const AAnimal* dog = new Dog();
	const AAnimal* cat = new Cat();
	std::cout << dog->getType() << std::endl;
	std::cout << cat->getType() << std::endl;
	dog->makeSound();
	cat->makeSound();

	std::cout << std::endl << "--- deep copy test ---" << std::endl;
	{
		Dog original;
		original.getBrain()->setIdea(0, "I want a bone");

		Dog copy(original);
		copy.getBrain()->setIdea(0, "I want a different bone");

		std::cout << "original idea 0: "
					<< original.getBrain()->getIdea(0) << std::endl;
		std::cout << "copy idea 0:     "
					<< copy.getBrain()->getIdea(0) << std::endl;

		std::string same = "no";
		if (original.getBrain() != copy.getBrain()) {
			same = "yes";
		}
		std::cout << "different Brain addresses: " << same << std::endl;
	}

	std::cout << std::endl << "--- delete via AAnimal* (virtual dtor) ---"
				<< std::endl;
	delete dog;
	delete cat;

	return 0;
}
