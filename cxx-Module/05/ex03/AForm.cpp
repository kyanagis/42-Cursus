#include "AForm.hpp"

#include "Bureaucrat.hpp"

AForm::AForm()
	: name_("default"),
		signed_(false),
		gradeToSign_(150),
		gradeToExecute_(150) {
}

AForm::AForm(const std::string& name, int gradeToSign, int gradeToExecute)
	: name_(name),
		signed_(false),
		gradeToSign_(gradeToSign),
		gradeToExecute_(gradeToExecute) {
	if (gradeToSign < 1 || gradeToExecute < 1)
		throw GradeTooHighException();
	if (gradeToSign > 150 || gradeToExecute > 150)
		throw GradeTooLowException();
}

AForm::AForm(const AForm& other)
	: name_(other.name_),
		signed_(other.signed_),
		gradeToSign_(other.gradeToSign_),
		gradeToExecute_(other.gradeToExecute_) {
}

AForm& AForm::operator=(const AForm& other) {
	if (this != &other)
		signed_ = other.signed_;
	return *this;
}

AForm::~AForm() {
}

const std::string& AForm::getName(void) const {
	return name_;
}

bool AForm::getSigned(void) const {
	return signed_;
}

int AForm::getGradeToSign(void) const {
	return gradeToSign_;
}

int AForm::getGradeToExecute(void) const {
	return gradeToExecute_;
}

void AForm::beSigned(const Bureaucrat& bureaucrat) {
	if (bureaucrat.getGrade() > gradeToSign_)
		throw GradeTooLowException();
	signed_ = true;
}

void AForm::execute(const Bureaucrat& executor) const {
	if (!signed_)
		throw NotSignedException();
	if (executor.getGrade() > gradeToExecute_)
		throw GradeTooLowException();
	execute_action();
}

const char* AForm::GradeTooHighException::what(void) const throw() {
	return "grade is too high";
}

const char* AForm::GradeTooLowException::what(void) const throw() {
	return "grade is too low";
}

const char* AForm::NotSignedException::what(void) const throw() {
	return "form is not signed";
}

std::ostream& operator<<(std::ostream& out, const AForm& form) {
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
