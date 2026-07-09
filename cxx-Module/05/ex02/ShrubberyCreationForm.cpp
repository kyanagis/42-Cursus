#include "ShrubberyCreationForm.hpp"

#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
	: AForm("ShrubberyCreationForm", 145, 137), target_("default") {
}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
	: AForm("ShrubberyCreationForm", 145, 137), target_(target) {
}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& other)
	: AForm(other), target_(other.target_) {
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(
	const ShrubberyCreationForm& other) {
	if (this != &other) {
		AForm::operator=(other);
		target_ = other.target_;
	}
	return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm() {
}

void ShrubberyCreationForm::execute_action(void) const {
	std::ofstream file((target_ + "_shrubbery").c_str());

	if (!file.is_open())
		throw std::exception();
	file << "           v .   ._, |_  .," << '\n';
	file << "        `-._\\/  .  \\ /    |/_" << '\n';
	file << "            \\  _\\, y | \\//" << '\n';
	file << "      _\\_.___\\, \\\\/ -.\\||" << '\n';
	file << "        `7-,--.`._||  / / ," << '\n';
	file << "        /'     `-. `./ / |/_.'" << '\n';
	file << "                  |    |//" << '\n';
	file << "                  |_    /" << '\n';
	file << "                  |-   |" << '\n';
	file << "                  |   =|" << '\n';
	file << "                  |    |" << '\n';
	file << "-----------------/ ,  . \\--------._" << '\n';
}
