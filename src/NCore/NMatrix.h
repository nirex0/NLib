// © 2019 NIREX ALL RIGHTS RESERVED

#ifndef _N_MATRIX_H_
#define _N_MATRIX_H_


#include "NDefines.h"


#include <iostream>
#include <sstream>
#include <vector>
#include <stdexcept>

namespace NLib
{
#pragma warning( disable : 4251 )

	template <class T>
	class NAPI NMatrix
	{
	PUBLIC:
		NMatrix<T>(int height, int width);
		NMatrix<T>(std::vector<std::vector<T>> const& array);
		NMatrix<T>(void);

		int GetHeight(void) const;
		int GetWidth(void) const;

		void Fill(const T& value);
		void Put(int h, int w, const T& value);
		T Get(int h, int w) const;

		NMatrix<T> Add(const NMatrix<T>& m) const;
		NMatrix<T> Subtract(const NMatrix<T>& m) const;
		NMatrix<T> Multiply(const NMatrix<T>& m) const;
		NMatrix<T> Dot(const NMatrix<T>& m) const;
		NMatrix<T> Transpose(void) const;
		NMatrix<T> Multiply(const T& value) const;
		NMatrix<T> Divide(const T& value) const;

		NMatrix<T> ApplyFunction(T(*function)(T)) const;
		NMatrix<T> Map(T(*function)(T)) const;
		NMatrix<T> SubMatrix(int startH, int startW, int h, int w) const;
		std::vector<T> ToVector(void) const;
		void FromVector(const std::vector<T>& inVec) const;

		void Print(std::ostream& flux) const;

		bool operator==(const NMatrix<T>& m);
		bool operator!=(const NMatrix<T>& m);
		NMatrix<T> operator+=(const NMatrix<T>& m);
		NMatrix<T> operator-=(const NMatrix<T>& m);
		NMatrix<T> operator*=(const NMatrix<T>& m);
		NMatrix<T> operator*=(const T& m);
		NMatrix<T> operator/=(const T& m);
		T& operator()(int y, int x);

	DATA:
		std::vector<std::vector<T>> array;
		int height;
		int width;
	};


	// Generic Matrix Functions
	template <class T> NMatrix<T> operator+(const NMatrix<T>& a, const NMatrix<T>& b);
	template <class T> NMatrix<T> operator-(const NMatrix<T>& a, const NMatrix<T>& b);
	template <class T> NMatrix<T> operator*(const NMatrix<T>& a, const NMatrix<T>& b);
	template <class T> NMatrix<T> operator*(const T& b, const NMatrix<T>& a);
	template <class T> NMatrix<T> operator/(const NMatrix<T>& a, const T& b);
	template <class T> std::ostream& operator<<(std::ostream& flux, const NMatrix<T>& m);

	typedef NMatrix<char> NMatC;
	typedef NMatrix<long> NMatL;
	typedef NMatrix<long long> NMatLL;

	typedef NMatrix<unsigned char> NMatUC;
	typedef NMatrix<unsigned long> NMatUL;
	typedef NMatrix<unsigned long long> NMatULL;

	typedef NMatrix<float> NMatF;
	typedef NMatrix<double> NMatD;
	typedef NMatrix<long double> NMatLD;

	template<typename T>
	using NMat = NMatrix<T>;

	template<typename T>
	using Matrix = NMatrix<T>;

	template<typename T>
	using Mat = NMatrix<T>;


	template <class T>
	NMatrix<T> operator+(const NMatrix<T>& a, const NMatrix<T>& b)
	{
		return a.Add(b);
	}

	template <class T>
	NMatrix<T> operator-(const NMatrix<T>& a, const NMatrix<T>& b)
	{
		return a.Subtract(b);
	}

	template <class T>
	NMatrix<T> operator*(const NMatrix<T>& a, const NMatrix<T>& b)
	{
		return a.Multiply(b);
	}

	template <class T>
	NMatrix<T> operator*(const T& b, const NMatrix<T>& a)
	{
		return a.Multiply(b);
	}

	template <class T>
	NMatrix<T> operator/(const NMatrix<T>& a, const T& b)
	{
		return a.Divide(b);
	}

	template <class T>
	std::ostream& operator<<(std::ostream& flux, const NMatrix<T>& m)
	{
		m.Print(flux);
		return flux;
	}


}

#endif // !_N_MATRIX_H_