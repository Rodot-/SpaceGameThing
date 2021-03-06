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

enum hb_flag {
        NONE = 0, 
        RADIAL = 1,
        RECT = 2,
        CONVEX = 4,
        PIXEL = 8 
        }//, RADIAL_ARR, RECT_ARR, CONVEX_ARR, PIXEL_ARR}; //types of possible collision methods specific to each object

inline hb_flag operator|(hb_flag a, hb_flag b)
	{return static_cast<hb_flag>(static_cast<int>(a) | static_cast<int>(b))};

inline hb_flag operator&(hb_flag a, hb_flag b)
	{return static_cast<hb_flag>(static_cast<int>(a) & static_cast<int>(b))};

inline hb_flag operator^(hb_flag a, hb_flag b)
	{return static_cast<hb_flag>(static_cast<int>(a) ^ static_cast<int>(b))};

};


class HitBox {

	public:

		HitBox();
		HitBox(void*, hb_flag);
		~HitBox();

		void* GetGeometry(); //return the transformed hitbox geometry

		hb_flag GetFlag() const; //get collision type

	private:

		void* _geometry;  //the base hitbox geometry
		hb_flag _flag; //the type of hitbox
};

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
		T GetHitBox() const; //get the transformed hitbox
		void SetTransform(const sf::Transform& transform);

		collision::type GetCollision() const; //get the collision method

		T _hbox; //The actual hitbox
	private:
		
		template <class T2>
		bool _hasCollided(const T2& other) const; //specific case collisions (polymorphic facillitator)
		sf::Transform _transform;
		//unsigned int _is_arr:1 // binary flag indicating the hitbox is an array (Could just make the hitbox object an array by default, for now though I wont even worry about it)
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
void HitBoxBase<T>::SetTransform(const sf::Transform& transform) {
	_transform = transform;
}

template <class T>
template <class T2>
bool HitBoxBase<T>::HasCollided(const HitBoxBase<T2>& other) const {

	return _hasCollided(other.GetHitBox());
};

template <> 
template <class T2>
bool HitBoxBase<std::pair<sf::Vector2f, float> >::_hasCollided(const T2& other) const {
	return CollisionDetected(GetHitBox(), other);
	//return true;
};

template <> 
template <class T2>
bool HitBoxBase<sf::ConvexShape>::_hasCollided(const T2& other) const {
	return CollisionDetected(GetHitBox(), other);
	return true;
};

template <> 
template <class T2>
bool HitBoxBase<sf::FloatRect>::_hasCollided(const T2& other) const {
	return CollisionDetected(GetHitBox(), other);
	return true;
};




#endif


