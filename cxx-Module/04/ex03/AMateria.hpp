#ifndef AMATERIA_HPP
#define AMATERIA_HPP

#include <string>

class ICharacter;

class AMateria {
public:
	AMateria();
	explicit AMateria(const std::string& type);
	AMateria(const AMateria& other);
	AMateria& operator=(const AMateria& other);
	virtual ~AMateria();

	const std::string& getType(void) const;

	virtual AMateria* clone(void) const = 0;
	virtual void use(ICharacter& target);

protected:
	std::string type_;
};

#endif
