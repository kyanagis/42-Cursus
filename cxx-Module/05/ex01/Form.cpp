#include "Form.hpp"

#include "Bureaucrat.hpp"

Form::Form()
	: name_("default"),
		signed_(false),
		gradeToSign_(150),
		gradeToExecute_(150) {
}

Form::Form(const std::string& name, int gradeToSign, int gradeToExecute)
	: name_(name),
		signed_(false),
		gradeToSign_(gradeToSign),
		gradeToExecute_(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

Form::Form(const Form& other)
	: name_(other.name_),
		signed_(other.signed_),
		gradeToSign_(other.gradeToSign_),
		gradeToExecute_(other.gradeToExecute_) {
}

Form& Form::operator=(const Form& other) {
	if (this != &other)
		signed_ = other.signed_;
	return *this;
}

Form::~Form() {
}

const std::string& Form::getName(void) const {
	return name_;
}

bool Form::getSigned(void) const {
	return signed_;
}

int Form::getGradeToSign(void) const {
	return gradeToSign_;
}

int Form::getGradeToExecute(void) const {
	return gradeToExecute_;
}

void Form::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > gradeToSign_)
		throw GradeTooLowException();
	signed_ = true;
}

const char* Form::GradeTooHighException::what(void) const throw() {
	return "grade is too high";
}

const char* Form::GradeTooLowException::what(void) const throw() {
	return "grade is too low";
}

std::ostream& operator<<(std::ostream& out, const Form& form) {
	out << "Form " << form.getName() << " [grade to sign: "
		<< form.getGradeToSign() << ", grade to execute: "
		<< form.getGradeToExecute() << ", signed: ";
	if (form.getSigned())
		out << "yes";
	else
		out << "no";
	out << "]";
	return out;
}
