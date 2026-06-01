#include "Harl.hpp"

#include <iostream>
#include <string>

Harl::Harl() {
}

Harl::~Harl() {
}

void Harl::debug(void) {
	std::cout << "[ DEBUG ]" << std::endl;
	std::cout << "I love having extra bacon for my "
			  << "7XL-double-cheese-triple-pickle-special-ketchup burger. "
			  << "I really do!" << std::endl;
	std::cout << std::endl;
}

void Harl::info(void) {
	std::cout << "[ INFO ]" << std::endl;
	std::cout << "I cannot believe adding extra bacon costs more money. "
			  << "You didn't put enough bacon in my burger! "
			  << "If you did, I wouldn't be asking for more!" << std::endl;
	std::cout << std::endl;
}

void Harl::warning(void) {
	std::cout << "[ WARNING ]" << std::endl;
	std::cout << "I think I deserve to have some extra bacon for free. "
			  << "I've been coming for years, whereas you started working "
			  << "here just last month." << std::endl;
	std::cout << std::endl;
}

void Harl::error(void) {
	std::cout << "[ ERROR ]" << std::endl;
	std::cout << "This is unacceptable! I want to speak to the manager now."
			  << std::endl;
	std::cout << std::endl;
}

int Harl::levelToIndex(const std::string& level) const {
	const std::string kLevels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	for (int i = 0; i < 4; ++i) {
		if (level == kLevels[i]) {
			return i;
		}
	}
	return -1;
}

void Harl::filter(const std::string& level) {
	switch (levelToIndex(level)) {
	case 0:
		debug();
	case 1:
		info();
	case 2:
		warning();
	case 3:
		error();
		break;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]"
				  << std::endl;
		break;
	}
}
