#include <cstdlib>
#include <ctime>
#include <iostream>

#include "AForm.hpp"
#include "Bureaucrat.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

int main(void) {
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	std::cout << "=== Execute an unsigned form ===" << '\n';
	{
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("garden");
		boss.executeForm(shrub);
	}

	std::cout << "\n=== Sign then execute a shrubbery form ===" << '\n';
	{
		Bureaucrat boss("Boss", 1);
		ShrubberyCreationForm shrub("garden");
		boss.signForm(shrub);
		boss.executeForm(shrub);
	}

	std::cout << "\n=== Grade too low to execute ===" << '\n';
	{
		Bureaucrat weak("Weak", 50);
		PresidentialPardonForm pardon("Bender");
		Bureaucrat boss("Boss", 1);
		boss.signForm(pardon);
		weak.executeForm(pardon);
	}

	std::cout << "\n=== Robotomy (50% success) ===" << '\n';
	{
		Bureaucrat boss("Boss", 1);
		RobotomyRequestForm robo("Bender");
		boss.signForm(robo);
		boss.executeForm(robo);
		boss.executeForm(robo);
		boss.executeForm(robo);
		boss.executeForm(robo);
	}

	std::cout << "\n=== Presidential pardon ===" << '\n';
	{
		Bureaucrat boss("Boss", 1);
		PresidentialPardonForm pardon("Marvin");
		boss.signForm(pardon);
		boss.executeForm(pardon);
	}

	return 0;
}
