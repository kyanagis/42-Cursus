#include <iostream>
#include <string>

#include "Input.hpp"
#include "PhoneBook.hpp"

namespace {

const char	*kCommandPrompt = "Enter command (ADD/SEARCH/EXIT): ";

bool execute_command(const std::string &command, PhoneBook &phone_book) {
	if (command == "ADD") {
		return phone_book.add_contact();
	}
	if (command == "SEARCH") {
		return phone_book.search_contacts();
	}
	return command != "EXIT";
}

}

int main(void) {
	PhoneBook	phone_book;
	std::string	command;
	bool		is_too_long;

	while (true) {
		std::cout << kCommandPrompt;
		if (!read_bounded_line(command, is_too_long)) {
			std::cout << '\n';
			break;
		}
		if (is_too_long) {
			continue;
		}
		if (!execute_command(command, phone_book)) {
			break;
		}
	}
	return 0;
}
