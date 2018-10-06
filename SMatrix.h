#pragma once
#include <cstddef>

/*
*An optimized square matrix class
*Assumes T is a primitive type
*/
template<class T>
class SMatrix
{
private:
	T * data;
	size_t size;
public:
	//Constructor
	SMatrix(size_t initSide = 8);
	SMatrix(size_t initSide, T fill);
	//Big 5
	SMatrix(const SMatrix<T> & other);
	SMatrix(SMatrix<T> && other);
	void operator=(const SMatrix<T> & other);
	void operator=(SMatrix<T> && other);
	~SMatrix();

	T & operator()(size_t row, size_t col);
	const T & operator()(size_t row, size_t col) const;
	T get(size_t row, size_t col) const;
	void resize(size_t newSide);
	void resize(size_t newSide, T fill);
	void set(size_t row, size_t col, T x);
	size_t side() const;
};

template<class T>
inline SMatrix<T>::SMatrix(size_t initSide)
	:data(new T[initSide*initSide]), size(initSide)
{}

template<class T>
inline SMatrix<T>::SMatrix(size_t initSide, T fill)
	:data(new T[initSide*initSide]), size(initSide)
{
	size_t arrSize = size * size;
	for (size_t i = 0; i < arrSize; ++i)
		data[i] = fill;
}

template<class T>
inline SMatrix<T>::SMatrix(const SMatrix & other)
	:data(new T[other.size*other.size]), size(other.size)
{
	size_t arrSize = size * size;
	for (size_t i = 0; i < arrSize; ++i)
		data[i] = other.data[i];
}

template<class T>
inline SMatrix<T>::SMatrix(SMatrix && other)
	:data(other.data), size(other.size)
{
	other.data = nullptr;
	other.size = 0;
}

template<class T>
inline void SMatrix<T>::operator=(const SMatrix & other)
{
	delete[] data;
	data = new T[other.size*other.size];
	size = other.size;
	size_t arrSize = size * size;
	for (size_t i = 0; i < arrSize; ++i)
		data[i] = other.data[i];
}

template<class T>
inline void SMatrix<T>::operator=(SMatrix && other)
{
	delete[] data;
	data = other.data;
	size = other.size;
	other.data = nullptr;
	other.size = 0;
}

template<class T>
inline SMatrix<T>::~SMatrix()
{
	delete[] data;
}

template<class T>
inline T & SMatrix<T>::operator()(size_t row, size_t col)
{
	return data[row * size + col];
}

template<class T>
inline const T & SMatrix<T>::operator()(size_t row, size_t col) const
{
	return data[row * size + col];
}

template<class T>
inline T SMatrix<T>::get(size_t row, size_t col) const
{
	return data[row * size + col];
}

template<class T>
inline void SMatrix<T>::resize(size_t newSide)
{
	T * temp = new T[newSide*newSide];
	size_t limit = (newSide < size) ? newSide : size;
	for (size_t i = 0; i < limit; ++i)
		for (size_t j = 0; j < limit; ++j)
			temp[i * newSide + j] = get(i, j);
	delete[] data;
	data = temp;
	size = newSide;
}

template<class T>
inline void SMatrix<T>::resize(size_t newSide, T fill)
{
	delete[] data;
	data = new T[newSide*newSide];
	size = newSide;
	size_t arrSize = size * size;
	for (size_t i = 0; i < arrSize; ++i)
		data[i] = fill;
}

template<class T>
inline void SMatrix<T>::set(size_t row, size_t col, T x)
{
	data[row * size + col] = x;
}

template<class T>
inline size_t SMatrix<T>::side() const
{
	return size;
}
