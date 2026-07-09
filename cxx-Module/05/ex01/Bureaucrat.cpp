#include "Bureaucrat.hpp"

#include "Form.hpp"

Bureaucrat::Bureaucrat() : name_("default"), grade_(150) {
}

Bureaucrat::Bureaucrat(const std::string& name, int grade)
	: name_(name), grade_(grade) {
	if (grade < 1)
		throw GradeTooHighException();
	if (grade > 150)
		throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
	: name_(other.name_), grade_(other.grade_) {
}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& other) {
	if (this != &other)
		grade_ = other.grade_;
	return *this;
}

Bureaucrat::~Bureaucrat() {
}

const std::string& Bureaucrat::getName(void) const {
	return name_;
}

int Bureaucrat::getGrade(void) const {
	return grade_;
}

void Bureaucrat::incrementGrade(void) {
	if (grade_ - 1 < 1)
		throw GradeTooHighException();
	--grade_;
}

void Bureaucrat::decrementGrade(void) {
	if (grade_ + 1 > 150)
		throw GradeTooLowException();
	++grade_;
}

void Bureaucrat::signForm(Form& form) const {
	try {
		form.beSigned(*this);
		std::cout << getName() << " signed " << form.getName() << '\n';
	} catch (std::exception& e) {
		std::cout << getName() << " couldn't sign " << form.getName()
					<< " because " << e.what() << "." << '\n';
	}
}

const char* Bureaucrat::GradeTooHighException::what(void) const throw() {
	return "grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw() {
	return "grade is too low";
}

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat) {
	out << bureaucrat.getName() << ", bureaucrat grade "
		<< bureaucrat.getGrade() << ".";
	return out;
}
