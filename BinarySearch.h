#pragma once
#include <limits>
#include <vector>

//Searches v for an element that compares equal to key. The elements on [min, max) are considered.
//v must be sorted on [min, max)
//Returns the index of the element that matches the key. If the key is not found returns std::numeric_limits<size_t>::max().
template <class T>
size_t binarySearch(const std::vector<T> & v, const T & key, size_t min, size_t max)
{
	while (min < max)
	{
		size_t mid = (min + max) / 2;
		if (key < v[mid])
			max = mid;
		else if (key > v[mid])
			min = mid + 1;
		else
			return mid;
	}

	return std::numeric_limits<size_t>::max();
}

//Searches v for an element that compares equal to key. All elements are considered.
//v must be sorted
//Returns the index of the element that matches the key. If the key is not found returns std::numeric_limits<size_t>::max().
template <class T>
size_t binarySearch(const std::vector<T> & v, const T & key)
{
	return binarySearch(v, key, 0, v.size());
}
