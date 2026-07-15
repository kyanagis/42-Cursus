#include "Array.hpp"
#include <iostream>
#include <string>

int main(void)
{
	std::cout << "--- empty array ---" << std::endl;
	Array<int> empty;
	std::cout << "size = " << empty.size() << std::endl;

	std::cout << "--- array of 5 ints (default-initialized) ---" << std::endl;
	Array<int> numbers(5);
	std::cout << "size = " << numbers.size() << std::endl;
	for (unsigned int i = 0; i < numbers.size(); ++i)
		std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;

	std::cout << "--- fill and read ---" << std::endl;
	for (unsigned int i = 0; i < numbers.size(); ++i)
		numbers[i] = static_cast<int>(i) * 10;
	for (unsigned int i = 0; i < numbers.size(); ++i)
		std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;

	std::cout << "--- deep copy (copy constructor) ---" << std::endl;
	Array<int> copy(numbers);
	copy[0] = 999;
	std::cout << "numbers[0] = " << numbers[0] << " (stays 0)" << std::endl;
	std::cout << "copy[0]    = " << copy[0] << " (is 999)" << std::endl;

	std::cout << "--- deep copy (assignment) ---" << std::endl;
	Array<int> assigned;
	assigned = numbers;
	assigned[1] = 777;
	std::cout << "numbers[1]  = " << numbers[1] << " (stays 10)" << std::endl;
	std::cout << "assigned[1] = " << assigned[1] << " (is 777)" << std::endl;

	std::cout << "--- out of bounds (read) ---" << std::endl;
	try
	{
		std::cout << numbers[42] << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught: " << e.what() << std::endl;
	}

	std::cout << "--- out of bounds on empty array ---" << std::endl;
	try
	{
		empty[0] = 1;
	}
	catch (const std::exception& e)
	{
		std::cout << "caught: " << e.what() << std::endl;
	}

	std::cout << "--- const array access ---" << std::endl;
	const Array<int> const_arr(numbers);
	std::cout << "const_arr[2] = " << const_arr[2] << std::endl;

	std::cout << "--- string array ---" << std::endl;
	Array<std::string> words(3);
	words[0] = "hello";
	words[1] = "template";
	words[2] = "world";
	for (unsigned int i = 0; i < words.size(); ++i)
		std::cout << "words[" << i << "] = " << words[i] << std::endl;

	return 0;
}
