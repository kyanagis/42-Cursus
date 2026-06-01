#include <iostream>
#include <string>

int main(void) {
	std::string brain = "HI THIS IS BRAIN";
	std::string* stringPTR = &brain;
	std::string& stringREF = brain;

	std::cout << "Address of the string variable: " << &brain << std::endl;
	std::cout << "Address held by stringPTR:      " << stringPTR << std::endl;
	std::cout << "Address held by stringREF:      " << &stringREF << std::endl;

	std::cout << std::endl;

	std::cout << "Value of the string variable: " << brain << std::endl;
	std::cout << "Value pointed to by stringPTR: " << *stringPTR << std::endl;
	std::cout << "Value pointed to by stringREF: " << stringREF << std::endl;

	return 0;
}
