#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <string>

class Weapon {
public:
	Weapon();
	explicit Weapon(const std::string& type);
	Weapon(const Weapon& other);
	Weapon& operator=(const Weapon& other);
	~Weapon();

	const std::string& getType(void) const;
	void setType(const std::string& type);

private:
	std::string type_;
};

#endif
