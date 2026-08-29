#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>

// RPN evaluates a Reverse Polish Notation expression. A std::stack is the
// natural fit: operands are pushed as they are read and each operator pops its
// two operands and pushes the result back, so the top of the stack always
// holds the running value.

class RPN {
public:
	RPN();
	RPN(const RPN& other);
	RPN& operator=(const RPN& other);
	~RPN();

	int evaluate(const std::string& expression);

private:
	std::stack<int> stack_;

	void apply(char op);
};

#endif
