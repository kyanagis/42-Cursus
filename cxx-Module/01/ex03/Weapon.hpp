#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
public:
	explicit Weapon(const std::string& type);

	const std::string& getType(void) const;
	void setType(const std::string& type);

private:
	std::string type_;
};

inline const std::string& Weapon::getType(void) const {
	return type_;
}

inline void Weapon::setType(const std::string& type) {
	type_ = type;
}

#endif
