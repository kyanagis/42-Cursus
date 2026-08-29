#include "RPN.hpp"

#include <sstream>
#include <stdexcept>

RPN::RPN() {
}

RPN::RPN(const RPN& other) : stack_(other.stack_) {
}

RPN& RPN::operator=(const RPN& other) {
	if (this != &other) {
		stack_ = other.stack_;
	}
	return *this;
}

RPN::~RPN() {
}

void RPN::apply(char op) {
	if (stack_.size() < 2) {
		throw std::runtime_error("not enough operands");
	}
	int b = stack_.top();
	stack_.pop();
	int a = stack_.top();
	stack_.pop();
	int result = 0;
	if (op == '+') {
		result = a + b;
	} else if (op == '-') {
		result = a - b;
	} else if (op == '*') {
		result = a * b;
	} else {
		if (b == 0) {
			throw std::runtime_error("division by zero");
		}
		result = a / b;
	}
	stack_.push(result);
}

int RPN::evaluate(const std::string& expression) {
	while (!stack_.empty()) {
		stack_.pop();
	}
	std::istringstream stream(expression);
	std::string token;
	while (stream >> token) {
		if (token.size() != 1) {
			throw std::runtime_error("invalid token");
		}
		char c = token[0];
		if (c >= '0' && c <= '9') {
			stack_.push(c - '0');
		} else if (c == '+' || c == '-' || c == '*' || c == '/') {
			apply(c);
		} else {
			throw std::runtime_error("invalid token");
		}
	}
	if (stack_.size() != 1) {
		throw std::runtime_error("invalid expression");
	}
	return stack_.top();
}
