#pragma once
#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact {
public:
	Contact(void);

	void	set(
		const std::string &first_name,
		const std::string &last_name,
		const std::string &nickname,
		const std::string &phone_number,
		const std::string &darkest_secret
	);
	const std::string	&get_first_name(void) const;
	const std::string	&get_last_name(void) const;
	const std::string	&get_nickname(void) const;
	const std::string	&get_phone_number(void) const;
	const std::string	&get_darkest_secret(void) const;

private:
	std::string	first_name_;
	std::string	last_name_;
	std::string	nickname_;
	std::string	phone_number_;
	std::string	darkest_secret_;
};

#endif
