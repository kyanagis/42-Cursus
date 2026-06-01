#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
public:
	Zombie();
	explicit Zombie(const std::string& name);
	~Zombie();

	void announce(void) const;
	void setName(const std::string& name);

private:
	std::string name_;
};

Zombie* newZombie(std::string name);

void randomChump(std::string name);

#endif
