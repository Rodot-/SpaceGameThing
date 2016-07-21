//vector/matrix math library

#ifndef V_MATH_H
#define V_MATH_H

#include "SFML/Graphics.hpp"

template <typename T>
sf::Vector2<T> dot_prod(sf::Vector2<T> A, sf::Vector2<T> B); //dot product

template <typename T>
sf::Vector2<T> cross_prod(sf::Vector2<T> A, sf::Vector2<T> B); //cross product


#endif

