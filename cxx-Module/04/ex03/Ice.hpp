#ifndef ICE_HPP
#define ICE_HPP

#include "AMateria.hpp"

class ICharacter;

class Ice : public AMateria {
public:
	Ice();
	Ice(const Ice& other);
	Ice& operator=(const Ice& other);
	~Ice();

	AMateria* clone(void) const;
	void use(ICharacter& target);
};

#endif
