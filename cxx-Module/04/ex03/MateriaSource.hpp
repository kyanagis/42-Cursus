#ifndef MATERIASOURCE_HPP
#define MATERIASOURCE_HPP

#include <string>

#include "AMateria.hpp"
#include "IMateriaSource.hpp"

class MateriaSource : public IMateriaSource {
public:
	MateriaSource();
	MateriaSource(const MateriaSource& other);
	MateriaSource& operator=(const MateriaSource& other);
	~MateriaSource();

	void learnMateria(AMateria* m);
	AMateria* createMateria(const std::string& type);

private:
	static const int kMaxTemplates = 4;

	AMateria* templates_[kMaxTemplates];

	void clearTemplates(void);
	void copyTemplates(const MateriaSource& other);
};

#endif
