#include <iostream>
#include <string>

#include "Input.hpp"
#include "PhoneBook.hpp"

int main(void) {
	PhoneBook	phone_book;
	std::string	command;
	bool		is_too_long;

	while (true) {
		std::cout << "Enter command (ADD/SEARCH/EXIT): ";
		if (!read_bounded_line(&command, &is_too_long)) {
			std::cout << '\n';
			break;
		}
		if (is_too_long) {
			continue;
		}
		if (command == "ADD") {
			if (!phone_book.add_contact()) {
				break;
			}
		} else if (command == "SEARCH") {
			if (!phone_book.search_contacts()) {
				break;
			}
		} else if (command == "EXIT") {
			break;
		}
	}
	return 0;
}
