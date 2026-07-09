#ifndef AFORM_HPP
#define AFORM_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat;

class AForm {
public:
	AForm();
	AForm(const std::string& name, int gradeToSign, int gradeToExecute);
	AForm(const AForm& other);
	AForm& operator=(const AForm& other);
	virtual ~AForm();

	const std::string& getName(void) const;
	bool getSigned(void) const;
	int getGradeToSign(void) const;
	int getGradeToExecute(void) const;

	void beSigned(const Bureaucrat& bureaucrat);
	void execute(const Bureaucrat& executor) const;

	class GradeTooHighException : public std::exception {
	public:
		virtual const char* what(void) const throw();
	};

	class GradeTooLowException : public std::exception {
	public:
		virtual const char* what(void) const throw();
	};

	class NotSignedException : public std::exception {
	public:
		virtual const char* what(void) const throw();
	};

protected:
	virtual void execute_action(void) const = 0;

private:
	const std::string name_;
	bool signed_;
	const int gradeToSign_;
	const int gradeToExecute_;
};

std::ostream& operator<<(std::ostream& out, const AForm& form);

#endif
