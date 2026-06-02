#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <string>

class Zombie {
public:
	Zombie();
	~Zombie();

	void announce(void) const;
	void set_name(const std::string& name);

private:
	std::string name_;
};

Zombie* zombieHorde(int N, const std::string& name);

#endif
