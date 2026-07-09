#include "Intern.hpp"

#include <iostream>

#include "AForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

namespace {

AForm* create_shrubbery(const std::string& target) {
	return new ShrubberyCreationForm(target);
}

AForm* create_robotomy(const std::string& target) {
	return new RobotomyRequestForm(target);
}

AForm* create_pardon(const std::string& target) {
	return new PresidentialPardonForm(target);
}

}  // namespace

Intern::Intern() {
}

Intern::Intern(const Intern& other) {
	(void)other;
}

Intern& Intern::operator=(const Intern& other) {
	(void)other;
	return *this;
}

Intern::~Intern() {
}

AForm* Intern::makeForm(const std::string& formName,
						const std::string& target) const {
	const std::string names[3] = {
		"shrubbery creation", "robotomy request", "presidential pardon"};
	AForm* (*factories[3])(const std::string&) = {
		&create_shrubbery, &create_robotomy, &create_pardon};

	int i = 0;
	while (i < 3) {
		if (formName == names[i]) {
			AForm* form = factories[i](target);
			std::cout << "Intern creates " << form->getName() << '\n';
			return form;
		}
		++i;
	}
	std::cout << "Intern cannot create form: unknown form \"" << formName
				<< "\"" << '\n';
	return NULL;
}
