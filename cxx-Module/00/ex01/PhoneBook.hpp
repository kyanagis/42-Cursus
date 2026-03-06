#pragma once
#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <string>

#include "Contact.hpp"

class PhoneBook {
public:
	PhoneBook(void);

	bool	add_contact(void);
	bool	search_contacts(void) const;

private:
	static const int	kMaxContacts = 8;

	Contact	contacts_[kMaxContacts];
	int		size_;
	int		next_index_;

	void		display_list(void) const;
	void		display_contact(int index) const;
	bool		read_field(const std::string &prompt, std::string *value) const;
};

#endif
