#include "PresidentialPardonForm.hpp"

#include <iostream>

PresidentialPardonForm::PresidentialPardonForm()
	: AForm("PresidentialPardonForm", 25, 5), target_("default") {
}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
	: AForm("PresidentialPardonForm", 25, 5), target_(target) {
}

PresidentialPardonForm::PresidentialPardonForm(
	const PresidentialPardonForm& other)
	: AForm(other), target_(other.target_) {
}

PresidentialPardonForm& PresidentialPardonForm::operator=(
	const PresidentialPardonForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		target_ = other.target_;
	}
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
}

void PresidentialPardonForm::execute_action(void) const {
	std::cout << target_ << " has been pardoned by Zaphod Beeblebrox." << '\n';
}
