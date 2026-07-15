#ifndef ARRAY_TPP
#define ARRAY_TPP

#include "Array.hpp"
#include <stdexcept>

template <typename T>
Array<T>::Array() : _data(0), _size(0)
{
}

template <typename T>
Array<T>::Array(unsigned int n) : _data(0), _size(n)
{
	if (_size > 0)
		_data = new T[_size]();
}

template <typename T>
Array<T>::Array(const Array& other)
	: _data(0), _size(other._size)
{
	unsigned int i;

	if (_size == 0)
		return;
	_data = new T[_size]();
	i = 0;
	try
	{
		while (i < _size)
		{
			_data[i] = other._data[i];
			++i;
		}
	}
	catch (...)
	{
		delete[] _data;
		_data = 0;
		_size = 0;
		throw;
	}
}

template <typename T>
Array<T>& Array<T>::operator=(const Array& other)
{
	if (this != &other)
	{
		Array<T> tmp(other);
		T* old_data = _data;
		unsigned int old_size = _size;

		_data = tmp._data;
		_size = tmp._size;
		tmp._data = old_data;
		tmp._size = old_size;
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
