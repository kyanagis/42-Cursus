#include "RobotomyRequestForm.hpp"

#include <cstdlib>
#include <iostream>

RobotomyRequestForm::RobotomyRequestForm()
	: AForm("RobotomyRequestForm", 72, 45), target_("default") {
}

RobotomyRequestForm::RobotomyRequestForm(const std::string& target)
	: AForm("RobotomyRequestForm", 72, 45), target_(target) {
}

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& other)
	: AForm(other), target_(other.target_) {
}

RobotomyRequestForm& RobotomyRequestForm::operator=(
	const RobotomyRequestForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		target_ = other.target_;
	}
	return *this;
}

RobotomyRequestForm::~RobotomyRequestForm() {
}

void RobotomyRequestForm::execute_action(void) const {
	std::cout << "* Bzzzzt... drilling noises... Vrrrrr *" << '\n';
	if (std::rand() % 2 == 0)
		std::cout << target_ << " has been robotomized successfully." << '\n';
	else
		std::cout << "The robotomy of " << target_ << " failed." << '\n';
}
