#include <cstdlib>
#include <ctime>
#include <iostream>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main(void) {
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	Intern intern;
	Bureaucrat boss("Boss", 1);

	std::cout << "=== Intern makes a robotomy request form ===" << '\n';
	{
		AForm* form = intern.makeForm("robotomy request", "Bender");
		if (form != NULL) {
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Intern makes a shrubbery creation form ===" << '\n';
	{
		AForm* form = intern.makeForm("shrubbery creation", "garden");
		if (form != NULL) {
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Intern makes a presidential pardon form ===" << '\n';
	{
		AForm* form = intern.makeForm("presidential pardon", "Marvin");
		if (form != NULL) {
			boss.signForm(*form);
			boss.executeForm(*form);
			delete form;
		}
	}

	std::cout << "\n=== Intern receives an unknown form name ===" << '\n';
	{
		AForm* form = intern.makeForm("coffee making", "Fry");
		if (form != NULL) {
			delete form;
		}
	}

	return 0;
}
