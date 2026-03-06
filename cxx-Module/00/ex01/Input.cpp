#include "Input.hpp"

#include <iostream>

namespace {

const std::string::size_type	kMaxInputLength = 1024;

bool has_reached_input_limit(const std::string &value) {
	return value.length() == kMaxInputLength;
}

void discard_line(void) {
	int	ch;

	while (true) {
		ch = std::cin.get();
		if (!std::cin.good() || ch == '\n') {
			return;
		}
	}
}

}

bool read_bounded_line(std::string &value, bool &is_too_long) {
	int	ch;

	value.clear();
	is_too_long = false;
	while (true) {
		ch = std::cin.get();
		if (!std::cin.good()) {
			return !value.empty();
		}
		if (ch == '\n') {
			return true;
		}
		if (has_reached_input_limit(value)) {
			is_too_long = true;
			discard_line();
			return true;
		}
		value.push_back(static_cast<char>(ch));
	}
}
