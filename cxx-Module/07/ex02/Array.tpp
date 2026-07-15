#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"
#include <stdexcept>

template <typename T>
Array<T>::Array() : _data(new T[0]()), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _data(new T[n]()), _size(n)
{
}

template <typename T>
Array<T>::Array(const Array& other)
	: _data(new T[other._size]()), _size(other._size)
{
	unsigned int i;

	i = 0;
	while (i < _size)
	{
		_data[i] = other._data[i];
		++i;
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		T* new_data;
		unsigned int i;

		new_data = new T[other._size]();
		i = 0;
		while (i < other._size)
		{
			new_data[i] = other._data[i];
			++i;
		}
		delete[] _data;
		_data = new_data;
		_size = other._size;
	}
	return *this;
}

template <typename T>
Array<T>::~Array()
{
	delete[] _data;
}

template <typename T>
T& Array<T>::operator[](unsigned int index)
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of bounds");
	return _data[index];
}

template <typename T>
const T& Array<T>::operator[](unsigned int index) const
{
	if (index >= _size)
		throw std::out_of_range("Array: index out of bounds");
	return _data[index];
}

template <typename T>
unsigned int Array<T>::size() const
{
	return _size;
}

#endif
