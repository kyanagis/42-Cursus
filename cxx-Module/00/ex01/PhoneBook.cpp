#include "PhoneBook.hpp"

#include <cctype>
#include <climits>

#include <iomanip>
#include <iostream>

#include "Input.hpp"

namespace {

const int	kColumnWidth = 10;

bool is_space(char c) {
	return std::isspace(static_cast<unsigned char>(c)) != 0;
}

bool is_digit(char c) {
	return std::isdigit(static_cast<unsigned char>(c)) != 0;
}

bool is_blank(const std::string &value) {
	for (std::string::size_type i = 0; i < value.length(); ++i) {
		if (!is_space(value[i])) {
			return false;
		}
	}
	return true;
}

bool parse_index(const std::string &input, int *value_out) {
	int	value = 0;
	std::string::size_type	i = 0;

	while (i < input.length() && is_space(input[i])) {
		++i;
	}
	if (i == input.length()) {
		return false;
	}
	while (i < input.length()) {
		char	ch = input[i];

		if (is_space(ch)) {
			break;
		}
		if (!is_digit(ch)) {
			return false;
		}
		if (value > (INT_MAX - (ch - '0')) / 10) {
			return false;
		}
		value = value * 10 + (ch - '0');
		++i;
	}
	while (i < input.length()) {
		if (!is_space(input[i])) {
			return false;
		}
		++i;
	}
	*value_out = value;
	return true;
}

std::string format_column(const std::string &value) {
	if (value.length() > 10) {
		return value.substr(0, 9) + ".";
	}
	return value;
}

}

PhoneBook::PhoneBook(void)
	: size_(0), next_index_(0) {
}

bool PhoneBook::read_field(
	const std::string &prompt,
	std::string *value
) const {
	while (true) {
		bool	is_too_long;

		std::cout << prompt;
		if (!read_bounded_line(value, &is_too_long)) {
			std::cout << '\n';
			return false;
		}
		if (is_too_long) {
			std::cout << "Field is too long.\n";
			continue;
		}
		if (!is_blank(*value)) {
			return true;
		}
		std::cout << "Field cannot be empty.\n";
	}
}

bool PhoneBook::add_contact(void) {
	std::string	first_name;
	std::string	last_name;
	std::string	nickname;
	std::string	phone_number;
	std::string	darkest_secret;

	if (!read_field("First name: ", &first_name)) {
		return false;
	}
	if (!read_field("Last name: ", &last_name)) {
		return false;
	}
	if (!read_field("Nickname: ", &nickname)) {
		return false;
	}
	if (!read_field("Phone number: ", &phone_number)) {
		return false;
	}
	if (!read_field("Darkest secret: ", &darkest_secret)) {
		return false;
	}
	contacts_[next_index_].set(
		first_name,
		last_name,
		nickname,
		phone_number,
		darkest_secret
	);
	if (size_ < kMaxContacts) {
		++size_;
	}
	next_index_ = (next_index_ + 1) % kMaxContacts;
	std::cout << "Contact added.\n";
	return true;
}

void PhoneBook::display_list(void) const {
	std::cout << std::setw(kColumnWidth) << "Index" << "|"
		<< std::setw(kColumnWidth) << "First Name" << "|"
		<< std::setw(kColumnWidth) << "Last Name" << "|"
		<< std::setw(kColumnWidth) << "Nickname" << '\n';
	for (int i = 0; i < size_; ++i) {
		std::cout << std::setw(kColumnWidth) << i << "|"
			<< std::setw(kColumnWidth)
			<< format_column(contacts_[i].get_first_name())
			<< "|"
			<< std::setw(kColumnWidth)
			<< format_column(contacts_[i].get_last_name())
			<< "|"
			<< std::setw(kColumnWidth)
			<< format_column(contacts_[i].get_nickname())
			<< '\n';
	}
}

void PhoneBook::display_contact(int index) const {
	std::cout << "First name: " << contacts_[index].get_first_name() << '\n'
		<< "Last name: " << contacts_[index].get_last_name() << '\n'
		<< "Nickname: " << contacts_[index].get_nickname() << '\n'
		<< "Phone number: " << contacts_[index].get_phone_number() << '\n'
		<< "Darkest secret: " << contacts_[index].get_darkest_secret()
		<< '\n';
}

bool PhoneBook::search_contacts(void) const {
	std::string	input;
	int			index;
	bool		is_too_long;

	if (size_ == 0) {
		std::cout << "PhoneBook is empty.\n";
		return true;
	}
	display_list();
	std::cout << "Enter index: ";
	if (!read_bounded_line(&input, &is_too_long)) {
		std::cout << '\n';
		return false;
	}
	if (is_too_long) {
		std::cout << "Invalid index.\n";
		return true;
	}
	if (!parse_index(input, &index) || index >= size_) {
		std::cout << "Invalid index.\n";
		return true;
	}
	display_contact(index);
	return true;
}
