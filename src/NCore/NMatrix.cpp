// © 2019 NIREX ALL RIGHTS RESERVED

#include "NMatrix.h"

template <class T>
NMatrix<T>::NMatrix(int height, int width)
{
	this->height = height;
	this->width = width;
	this->array = std::vector<std::vector<T>>(height, std::vector<T>(width));
}

template <class T>
NMatrix<T>::NMatrix(std::vector<std::vector<T>> const& array)
{
	if (array.size() == 0)
	{
		throw std::invalid_argument("Size of array must be greater than 0.");
	}

	this->height = array.size();
	this->width = array[0].size();
	this->array = array;
}

template <class T>
NMatrix<T>::NMatrix(void)
{
	height = 0;
	width = 0;
}

template <class T>
int NMatrix<T>::GetHeight(void) const
{
	return height;
}

template <class T>
int NMatrix<T>::GetWidth(void) const
{
	return width;
}

template <class T>
void NMatrix<T>::Fill(const T& value)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			array[i][j] = value;
		}
	}
}

template <class T>
void NMatrix<T>::Put(int h, int w, const T& value)
{
	if (!(h >= 0 && h < height && w >= 0 && w < width))
	{
		throw std::invalid_argument("Index out of bounds.");
	}

	array[h][w] = value;
}

template <class T>
T NMatrix<T>::Get(int h, int w) const
{
	if (!(h >= 0 && h < height && w >= 0 && w < width))
	{
		throw std::invalid_argument("Index out of bounds.");
	}

	return array[h][w];
}

template <class T>
NMatrix<T> NMatrix<T>::Add(const NMatrix& m) const
{
	if (!(height == m.height && width == m.width))
	{
		throw std::invalid_argument("NMatrix dimension must be the same.");
	}

	NMatrix result(height, width);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result.array[i][j] = array[i][j] + m.array[i][j];
		}
	}

	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::Subtract(const NMatrix& m) const
{
	if (!(height == m.height && width == m.width))
	{
		throw std::invalid_argument("NMatrix dimension must be the same.");
	}

	NMatrix result(height, width);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result.array[i][j] = array[i][j] - m.array[i][j];
		}
	}
	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::Multiply(const NMatrix& m) const
{
	if (!(height == m.height && width == m.width))
	{
		throw std::invalid_argument("NMatrix dimension must be the same.");
	}

	NMatrix result(height, width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result.array[i][j] = array[i][j] * m.array[i][j];
		}
	}
	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::Dot(const NMatrix& m) const
{
	if (!(width == m.height))
	{
		throw std::invalid_argument("Dot product not compatible.");
	}

	T w = 0;
	int mwidth = m.width;

	NMatrix<T> result(height, mwidth);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < mwidth; j++)
		{
			for (int h = 0; h < width; h++)
			{
				w += array[i][h] * m.array[h][j];
			}
			result.array[i][j] = w;
			w = 0;
		}
	}

	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::Transpose(void) const
{
	NMatrix<T> result(width, height);

	for (int i = 0; i < width; i++)
	{
		for (int j = 0; j < height; j++)
		{
			result.array[i][j] = array[j][i];
		}
	}
	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::Multiply(const T& value) const
{
	NMatrix result(array);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result.array[i][j] *= value;
		}
	}

	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::Divide(const T& value) const
{
	NMatrix result(array);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result.array[i][j] /= value;
		}
	}

	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::ApplyFunction(T(*function)(T)) const
{
	NMatrix<T> result(height, width);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result.array[i][j] = (*function)(array[i][j]);
		}
	}

	return result;
}

template <class T>
NMatrix<T> NMatrix<T>::SubMatrix(int startH, int startW, int h, int w) const
{
	if (!(startH >= 0 && startH + h <= height && startW >= 0 && startW + w <= width))
		throw std::invalid_argument("Index out of bounds");

	NMatrix<T> result(h, w);
	for (int i = startH; i < startH + h; i++)
	{
		for (int j = startW; j < startW + w; j++)
		{
			result.array[i - startH][j - startW] = array[i][j];
		}
	}
	return result;
}

template<class T>
inline std::vector<T> NMatrix<T>::ToVector(void) const
{
	std::vector<T> result(height * width);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			result.push_back(array[i][j]);
		}
	}
	return result;
}

template<class T>
inline void NMatrix<T>::FromVector(const std::vector<T>& inVec) const
{
	if (inVec.size() !+ height * width)
	{
		return;
	}

	int x = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			mat(i, j) = image[x];
			x++;
		}
	}
}

template <class T>
void NMatrix<T>::Print(std::ostream& flux) const
{
	int maxLength[width] = {};
	std::stringstream ss;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ss << array[i][j];
			if (maxLength[j] < ss.str().size())
			{
				maxLength[j] = ss.str().size();
			}
			ss.str(std::string());
		}
	}

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			flux << array[i][j];
			ss << array[i][j];
			for (int k = 0; k < maxLength[j] - ss.str().size() + 1; k++)
			{
				flux << " ";
			}
			ss.str(std::string());
		}
		flux << std::endl;
	}
}

template <class T>
bool NMatrix<T>::operator==(const NMatrix& m)
{
	if (height == m.height && width == m.width)
	{
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (array[i][j] != m.array[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

template <class T>
bool NMatrix<T>::operator!=(const NMatrix& m)
{
	return !operator==(m);
}

template <class T>
NMatrix<T> NMatrix<T>::operator+=(const NMatrix& m)
{
	this->array = Add(m).array;
	return *this;
}

template <class T>
NMatrix<T> NMatrix<T>::operator-=(const NMatrix& m)
{
	this->array = Subtract(m).array;
	return *this;
}

template <class T>
NMatrix<T> NMatrix<T>::operator*=(const NMatrix& m)
{
	this->array = Multiply(m).array;
	return *this;
}

template <class T>
NMatrix<T> NMatrix<T>::operator*=(const T& m)
{
	*this = this->Multiply(m);
	return *this;
}

template <class T>
NMatrix<T> NMatrix<T>::operator/=(const T& m)
{
	*this = this->Divide(m);
	return *this;
}

template <class T>
T& NMatrix<T>::operator()(int y, int x)
{
	if (!(y >= 0 && y < height && x >= 0 && x < width))
	{
		throw std::invalid_argument("Index out of bounds.");
	}

	return array[y][x];
}
