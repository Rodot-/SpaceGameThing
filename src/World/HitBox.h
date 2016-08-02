/*Class that acts as a set of hitboxes for collision detection purposes.  
gameAssets should contain hitboxes
HitBoxes should update with animation frames
There should be multiple types of hitboxes
-Radial
-Convex
-Rect

-Radial Array
-Rect Array
-Convex Array
--Arrays might be superclasses of hitboxes, like a multi-hitbox thing

Hitboxes should be able to be generated in multiple ways
-By image maps
-By hardcode
-By script
-By specific gameAsset properties (like multi-asset, GeometryTiles)
*/

#ifndef HIT_BOX_H
#define HIT_BOX_H

#include "SFML/Graphics.hpp"
#include "../Math/Collision.h"
#include <vector>
#include <stdio.h>


/*T can be one of the following or a vector of the following
sf::Rect<T>
sf::ConvexShape
std::pair<sf::Vector2f, float> (a circle)
*/

template <class T> //T should be one of the above
class HitBoxBase { 
/*base hitbox class
Will handle basic collision detection
*/
	public:

		HitBoxBase();
		HitBoxBase(T hbox); //set the hitbox in the constructor
		~HitBoxBase();

		//void Set(T hbox); //set the hitbox	
		template <class T2>
		bool HasCollided(const HitBoxBase<T2>& other) const; //test for collision
		void UpdateCenter(float x, float y); //update the hitbox center

		collision::type GetCollision() const; //get the collision method

		T _hbox; //The actual hitbox
	private:
		
		template <class T2>
		bool _hasCollided(const T2& other) const; //specific case collisions (polymorphic facillitator)
};
//need some functions to return collision information


template <class T>
HitBoxBase<T>::HitBoxBase(void) { };

template <class T>
HitBoxBase<T>::HitBoxBase(T hbox) {

	_hbox = hbox;
};

template <class T> //need to do this for array types
HitBoxBase<T>::~HitBoxBase(void) {};


template <class T>
template <class T2>
bool HitBoxBase<T>::HasCollided(const HitBoxBase<T2>& other) const {

	return _hasCollided(other._hbox);
};

template <> 
template <class T2>
bool HitBoxBase<std::pair<sf::Vector2f, float> >::_hasCollided(const T2& other) const {
	printf("Circle\n");
	return CollisionDetected(_hbox, other);
	//return true;
};

template <> 
template <class T2>
bool HitBoxBase<sf::ConvexShape>::_hasCollided(const T2& other) const {
	//return CollisionDetected(_hbox, other);
	return true;
};

template <> 
template <class T2>
bool HitBoxBase<sf::FloatRect>::_hasCollided(const T2& other) const {
	//return CollisionDetected(_hbox, other);
	return true;
};




#endif


