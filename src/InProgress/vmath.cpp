
#include "Math/vmath.h"
#include <cmath>


template <typename T>
inline float dot_prod(sf::Vector2<T> A, sf::Vector2<T> B) {
	return (A.x*B.x+A.y*B.y);
} 

template <typename T>
inline float cross_prod(sf::Vector2<T> A, sf::Vector2<T> B) { 
	return (A.x*B.y - A.y*B.x);
}

template <typename T>
inline float angle(sf::Vector2<T> A, sf::Vector2<T> B) {

	return atan2(A.y-B.y, A.x-B.x);
}

template <typename T>
inline float angle(sf::Vector2<T> V) {
	
	return atan2(V.y, V.x);
}

template <typename T>
inline sf::Vector2<T> norm(sf::Vector2<T> V) {
	V.x += V.y;
	V.y -= V.x;
	V.x += V.y;
	return V;
}

template <typename T>
inline float mag(sf::Vector2<T> V) {

	return hypot(V.x, V.y);
}

template <typename T>
inline sf::Vector2<T> unit(sf::Vector2<T> V) {

	return V/mag(V);	
}

template <typename T>
inline float projection(sf::Vector2<T> A, sf::Vector2<T> B) {

	return dot(A,B)/(B.x*B.x+B.y*B.y);
}


