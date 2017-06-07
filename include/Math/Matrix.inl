#ifndef MATRIX_INL
#define MATRIC_INL


template <typename T>
Matrix2<T>::Matrix2() {};

template <typename T>
Matrix2<T>::Matrix2(T a, T b, T c, T d) : a(a), b(b), c(c), d(d) { };

template <typename U>
template <typename T>
Matrix2<T>::Matrix2(const Matrix2<U>& matrix) : a(matrix.a), b(matrix.b), c(matrix.c), d(matrix.d) { };


template <typename T>
Matrix2<T> operator-(const Matrix2<T>& right) {

	Matrix2<T> matrix = {a-right.a, b - right.b, c - right.c, d - right.d};
	return matrix;
};

template <typename T>
Matrix2<T> operator+=(Matrix2<T>& left, const Matrix2<T>& right) {

	left.a += right.a;
	left.b += right.b;
	left.c += right.c;
	left.d += right.d;
};

template <typename T>
Matrix2<T> operator-=(Matrix2<T>& left, const Matrix2<T>& right) {

	left.a -= right.a;
	left.b -= right.b;
	left.c -= right.c;
	left.d -= right.d;
};

template <typename T>
Matrix2<T> operator+(const Matrix2<T>& left, const Matrix2<T>& right) {

	Matrix2<T> matrix = {left.a+right.a, left.b+right.b, left.c+right.c, left.d+right.d};
	return matrix;
}

template <typename T>
Matrix2<T> operator-(const Matrix2<T>& left, const Matrix2<T>& right) {

	Matrix2<T> matrix = {left.a-right.a, left.b-right.b, left.c-right.c, left.d-right.d};
	return matrix;
}

template <typename T>
Matrix2<T> operator*(const Matrix2<T>& left, T right) {
	
	//TODO: later
}

#endif
