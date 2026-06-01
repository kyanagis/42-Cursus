#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <string>

#include "Weapon.hpp"

class HumanA {
public:
	HumanA(const std::string& name, Weapon& weapon);
	~HumanA();

	void attack(void) const;

private:
	std::string name_;
	Weapon& weapon_;
};

#endif
