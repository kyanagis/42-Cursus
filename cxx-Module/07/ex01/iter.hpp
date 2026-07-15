#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

template <typename T, typename F>
void iter(T* array, const std::size_t length, F func)
{
	std::size_t i;

	i = 0;
	while (i < length)
	{
		func(array[i]);
		++i;
	}
}

#endif
