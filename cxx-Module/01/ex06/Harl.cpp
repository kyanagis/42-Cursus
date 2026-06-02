#include "Harl.hpp"

#include <iostream>
#include <string>

Harl::Harl() {
}

Harl::~Harl() {
}

void Harl::debug(void) {
	std::cout << "[ DEBUG ]" << '\n';
	std::cout << "I love having extra bacon for my "
				<< "7XL-double-cheese-triple-pickle-special-ketchup burger. "
				<< "I really do!" << '\n';
	std::cout << '\n';
}

void Harl::info(void) {
	std::cout << "[ INFO ]" << '\n';
	std::cout << "I cannot believe adding extra bacon costs more money. "
				<< "You didn't put enough bacon in my burger! "
				<< "If you did, I wouldn't be asking for more!" << '\n';
	std::cout << '\n';
}

void Harl::warning(void) {
	std::cout << "[ WARNING ]" << '\n';
	std::cout << "I think I deserve to have some extra bacon for free. "
				<< "I've been coming for years, whereas you started working "
				<< "here just last month." << '\n';
	std::cout << '\n';
}

void Harl::error(void) {
	std::cout << "[ ERROR ]" << '\n';
	std::cout << "This is unacceptable! I want to speak to the manager now."
				<< '\n';
	std::cout << '\n';
}

int Harl::level_to_index(const std::string& level) const {
	static const std::string kLevels[4] = {
		"DEBUG", "INFO", "WARNING", "ERROR"
	};
	for (int i = 0; i < 4; ++i) {
		if (level == kLevels[i]) {
			return i;
		}
	}
	return -1;
}

void Harl::filter(const std::string& level) {
	switch (level_to_index(level)) {
	case 0:
		debug();
		// fall through
	case 1:
		info();
		// fall through
	case 2:
		warning();
		// fall through
	case 3:
		error();
		break;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]"
					<< '\n';
		break;
	}
}
