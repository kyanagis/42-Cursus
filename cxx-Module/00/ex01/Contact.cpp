#include "Contact.hpp"

Contact::Contact(void) {
}

void Contact::set(
	const std::string &first_name,
	const std::string &last_name,
	const std::string &nickname,
	const std::string &phone_number,
	const std::string &darkest_secret
) {
	first_name_ = first_name;
	last_name_ = last_name;
	nickname_ = nickname;
	phone_number_ = phone_number;
	darkest_secret_ = darkest_secret;
}

const std::string &Contact::get_first_name(void) const {
	return first_name_;
}

const std::string &Contact::get_last_name(void) const {
	return last_name_;
}

const std::string &Contact::get_nickname(void) const {
	return nickname_;
}

const std::string &Contact::get_phone_number(void) const {
	return phone_number_;
}

const std::string &Contact::get_darkest_secret(void) const {
	return darkest_secret_;
}
