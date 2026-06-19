#include "MateriaSource.hpp"

#include <string>

#include "AMateria.hpp"

MateriaSource::MateriaSource() {
	for (int i = 0; i < kMaxTemplates; ++i) {
		templates_[i] = NULL;
	}
}

MateriaSource::MateriaSource(const MateriaSource& other) : IMateriaSource() {
	for (int i = 0; i < kMaxTemplates; ++i) {
		templates_[i] = NULL;
	}
	copyTemplates(other);
}

MateriaSource& MateriaSource::operator=(const MateriaSource& other) {
	if (this != &other) {
		clearTemplates();
		copyTemplates(other);
	}
	return *this;
}

MateriaSource::~MateriaSource() {
	clearTemplates();
}

void MateriaSource::learnMateria(AMateria* m) {
	if (m == NULL) {
		return;
	}
	for (int i = 0; i < kMaxTemplates; ++i) {
		if (templates_[i] == NULL) {
			templates_[i] = m;
			return;
		}
	}
}

AMateria* MateriaSource::createMateria(const std::string& type) {
	for (int i = 0; i < kMaxTemplates; ++i) {
		if (templates_[i] != NULL && templates_[i]->getType() == type) {
			return templates_[i]->clone();
		}
	}
	return NULL;
}

void MateriaSource::clearTemplates(void) {
	for (int i = 0; i < kMaxTemplates; ++i) {
		delete templates_[i];
		templates_[i] = NULL;
	}
}

void MateriaSource::copyTemplates(const MateriaSource& other) {
	for (int i = 0; i < kMaxTemplates; ++i) {
		if (other.templates_[i] != NULL) {
			templates_[i] = other.templates_[i]->clone();
		}
	}
}
