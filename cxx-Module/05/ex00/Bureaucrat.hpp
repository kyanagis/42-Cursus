#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <exception>
#include <iostream>
#include <string>

class Bureaucrat {
public:
	Bureaucrat();
	Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& other);
	Bureaucrat& operator=(const Bureaucrat& other);
	~Bureaucrat();

	const std::string& getName(void) const;
	int getGrade(void) const;

	void incrementGrade(void);
	void decrementGrade(void);

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
	int grade_;
};

std::ostream& operator<<(std::ostream& out, const Bureaucrat& bureaucrat);

#endif
