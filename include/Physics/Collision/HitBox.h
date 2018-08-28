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
        CONVEX = 4
		}
		//, PIXEL = 8, RADIAL_ARR, RECT_ARR, CONVEX_ARR, PIXEL_ARR}; //types of possible collision methods specific to each object

inline hb_flag operator|(hb_flag a, hb_flag b)
	{return static_cast<hb_flag>(static_cast<unsigned int>(a) | static_cast<unsigned int>(b))};

inline hb_flag operator&(hb_flag a, hb_flag b)
	{return static_cast<hb_flag>(static_cast<unsigned int>(a) & static_cast<unsigned int>(b))};

inline hb_flag operator^(hb_flag a, hb_flag b)
	{return static_cast<hb_flag>(static_cast<unsigned int>(a) ^ static_cast<unsigned int>(b))};

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


#endif


