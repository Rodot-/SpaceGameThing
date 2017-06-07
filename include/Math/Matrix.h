//declare a matrix class in a similar fashion to the sfml Vector class
#ifndef MATRIX_H
#define MATRIX_H

template <typename T>
class Matrix2 {

	public:

		Matrix2();
		Matrix2(T a, T b, T c, T d);
		template <typename U>
		explicit Matrix2(const Matrix2<U>& matrix); //copy constructor

		//data
		/*[a b]
		  [c d]*/
		T a;
		T b;
		T c;
		T d;
};

template <typename T>
Matrix<T> operator-(const Matrix2<T>& right);

template <typename T>
Matrix<T> operator+=(Matrix2<T>& left, const Matrix2<T>& right);

template <typename T>
Matrix<T> operator-=(Matrix2<T>& left, const Matrix2<T>& right);

template <typename T>
Matrix<T> operator+(const Matrix2<T>& left, const Matrix2<T>& right);

template <typename T>
Matrix<T> operator-(const Matrix2<T>& left, const Matrix2<T>& right);

template <typename T>
Matrix<T> operator*(const Matrix2<T>& left, T right);

template <typename T>
Matrix<T> operator*(T left, const Matrix2<T>& right);

template <typename T>
Matrix<T> operator*=(Matrix2<T>& left, T right);

template <typename T>
Matrix2<T> operator/(const Matrix2<T>& left, T right);

template <typename T>
Matrix2<T> operator/=(Matrix2<T>& left, T right);

template <typename T>
bool operator==(const Matrix2<T>& left, const Matrix2<T>& right);

template <typename T>
bool operator!=(const Matrix2<T>& left, const Matrix2<T>& right);

#include "Matrix2.inl"
typedef Matrix2<int> Matrix2i;
typedef Matrix2<unsigned int> Matrix2u;
typedef Matrix2<float> Matrix2f;

#endif
