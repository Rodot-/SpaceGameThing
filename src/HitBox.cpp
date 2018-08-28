#include "World/HitBox.h"
#include <stdio.h>


HitBox::HitBox(void) : _flag(NONE) { }

HitBox::HitBox(void* geometry, hb_flag flag) : _geometry(geometry), _flag(flag) { }

~HitBox::HitBox() {
	delete _geometry;
}

void* GetGeometry() {
	return _geometry;
}

hb_flag GetFlag() const {
	return _flag;
}
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

//template <>
//void HitBoxBase<std::pair<sf::Vector2f, float> >::UpdateCenter(float x, float y) {

//	_hbox.first.x = x;
//	_hbox.first.y = y;
//}

template<>
sf::FloatRect HitBoxBase<sf::FloatRect>::GetHitBox(void) const {

	return _transform.transformRect(_hbox);
}

template<>
std::pair<sf::Vector2f, float> HitBoxBase<std::pair<sf::Vector2f, float> >::GetHitBox(void) const {

	return std::pair<sf::Vector2f, float>(_transform.transformPoint(_hbox.first), _hbox.second);
}

template<>
sf::ConvexShape HitBoxBase<sf::ConvexShape>::GetHitBox(void) const {

	sf::ConvexShape result = _hbox;
	for (int i = 0; i < result.getPointCount(); ++i) {
		result.setPoint(i, _transform.transformPoint(_hbox.getPoint(i)));
	}
	return result;
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


