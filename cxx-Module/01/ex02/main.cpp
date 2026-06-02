#include <iostream>
#include <string>

static void print_addresses(const std::string& brain, const std::string* ptr,
							const std::string& ref) {
	std::cout << "Address of the string variable: " << &brain << '\n';
	std::cout << "Address held by stringPTR:      " << ptr << '\n';
	std::cout << "Address held by stringREF:      " << &ref << '\n';
}

static void print_values(const std::string& brain, const std::string* ptr,
							const std::string& ref) {
	std::cout << "Value of the string variable: " << brain << '\n';
	std::cout << "Value pointed to by stringPTR: " << *ptr << '\n';
	std::cout << "Value pointed to by stringREF: " << ref << '\n';
}

int main(void) {
	std::string brain = "HI THIS IS BRAIN";
	std::string* stringPTR = &brain;
	std::string& stringREF = brain;

	print_addresses(brain, stringPTR, stringREF);
	std::cout << '\n';
	print_values(brain, stringPTR, stringREF);

	return 0;
}
