#include "World/HitBox.h"
#include <stdio.h>
/*
template <class T>
HitBoxBase<T>::HitBoxBase(void) { }

template <class T>
HitBoxBase<T>::HitBoxBase(T hbox) {

	_hbox = hbox;
}

template <class T> //need to do this for array types
HitBoxBase<T>::~HitBoxBase(void) {}


template <class T>
template <class T2>
bool HitBoxBase<T>::HasCollided(const HitBoxBase<T2>& other) const {

	return _hasCollided(other._hbox);
}
*/
//return a different collision method depending on the type

template <>
void HitBoxBase<std::pair<sf::Vector2f, float> >::UpdateCenter(float x, float y) {

	_hbox.first.x = x;
	_hbox.first.y = y;
}

template <>
void HitBoxBase<sf::FloatRect>::UpdateCenter(float x, float y) {

	_hbox.left = x+_hbox.width/2;
	_hbox.top = y+_hbox.height/2;
}

template <>
void HitBoxBase<sf::ConvexShape>::UpdateCenter(float x, float y) {

	_hbox.setPosition(x, y);
}

template <> 
collision::type HitBoxBase<std::pair<sf::Vector2f, float> >::GetCollision(void) const {
	return collision::RADIAL;
}

template <> 
collision::type HitBoxBase<sf::ConvexShape>::GetCollision(void) const {
	return collision::CONVEX;
}

template <> 
collision::type HitBoxBase<sf::FloatRect>::GetCollision(void) const {
	return collision::RECT;
}
/*
template <>
collision::type HitBoxBase<sf::Image>::GetCollision(void) const {
	return collision::PIXEL;
}
*/
//template collision facillitators
template <> 
template <class T2>
bool HitBoxBase<std::pair<sf::Vector2f, float> >::_hasCollided(const T2& other) const {
	printf("Circle\n");
	return CollisionDetected(_hbox, other);
	//return true;
}

template <> 
template <class T2>
bool HitBoxBase<sf::ConvexShape>::_hasCollided(const T2& other) const {
	printf("Convex\n");
	//return CollisionDetected(_hbox, other);
	return true;
}

template <> 
template <class T2>
bool HitBoxBase<sf::FloatRect>::_hasCollided(const T2& other) const {
	//return CollisionDetected(_hbox, other);
	printf("FloatRect\n");
	return true;
}
/*
template <>
template <class T2>
bool HitBoxBase<sf::Image>::_hasCollided(const T2& other) const {
	return true; //TODO
	//return CollisionDetected(_hbox, other);
}
*/


