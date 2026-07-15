#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void print(const T& value)
{
	std::cout << value << std::endl;
}

template <typename T>
void increment(T& value)
{
	value += 1;
}

void shout(const std::string& word)
{
	std::cout << word << "!" << std::endl;
}

int main(void)
{
	int numbers[] = {1, 2, 3, 4, 5};
	const std::size_t int_len = sizeof(numbers) / sizeof(numbers[0]);

	std::cout << "--- print ints ---" << std::endl;
	iter(numbers, int_len, print<int>);

	std::cout << "--- increment then print ---" << std::endl;
	iter(numbers, int_len, increment<int>);
	iter(numbers, int_len, print<int>);

	float decimals[] = {1.1f, 2.2f, 3.3f};
	const std::size_t float_len = sizeof(decimals) / sizeof(decimals[0]);

	std::cout << "--- print floats ---" << std::endl;
	iter(decimals, float_len, print<float>);

	std::string words[] = {"hello", "template", "world"};
	const std::size_t word_len = sizeof(words) / sizeof(words[0]);

	std::cout << "--- shout strings ---" << std::endl;
	iter(words, word_len, shout);

	std::cout << "--- const array with print ---" << std::endl;
	const int const_numbers[] = {10, 20, 30};
	iter(const_numbers, 3, print<int>);

	return 0;
}
