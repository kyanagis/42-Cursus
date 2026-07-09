#ifndef FORM_HPP
#define FORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class Form {
public:
	Form();
	Form(const std::string& name, int gradeToSign, int gradeToExecute);
	Form(const Form& other);
	Form& operator=(const Form& other);
	~Form();

	const std::string& getName(void) const;
	bool getSigned(void) const;
	int getGradeToSign(void) const;
	int getGradeToExecute(void) const;

	void beSigned(const Bureaucrat& bureaucrat);

	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what(void) const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what(void) const throw();
	};

private:
	const std::string name_;
	bool signed_;
	const int gradeToSign_;
	const int gradeToExecute_;
};

std::ostream& operator<<(std::ostream& out, const Form& form);

#endif
