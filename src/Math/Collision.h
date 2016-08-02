//library of boolean fucntions for determining collisions from various types

#ifndef COLLISION_H
#define COLLISION_H

#include "SFML/Graphics.hpp"
//#include "../World/gameAssets.h"
#include <cmath>
#include "vmath.h"
//#include "../World/gameAssets.h"



namespace collision { //namespace containing various collision specific properties

	enum type {RADIAL, RECT, CONVEX, PIXEL, RADIAL_ARR, RECT_ARR, CONVEX_ARR, PIXEL_ARR}; //types of possible collision methods specific to each object
};

inline bool RadialRadial(const sf::Vector2f& p1, float r1, const sf::Vector2f& p2, float r2);
/* Determine if there is a collision between two radially 
	colliding objects centered at p1 and p2 with radii r1 
	and r2 respectively */ 

inline bool RectRect(const sf::FloatRect& R1, const sf::FloatRect& R2);
/* determine if two float rects intersct */

inline bool RadialRect(const sf::Vector2f& p1, float r1, const sf::FloatRect& R1);
/* determine if a rectangle and a circle collide 
	later, rewrite so the order does not matter*/

inline bool RadialLine(const sf::Vector2f& p1, float r1, const sf::Vector2f& A, const sf::Vector2f& B);
/* see if a line intersects of circle */

inline bool LineLine(const sf::Vector2f& a1, const sf::Vector2f& a2, const sf::Vector2f& b1, const sf::Vector2f& b2); 
/*see if two lines defined as A = {a1, a2}, B = {b1, b2} intesect one another*/

inline bool ConvexConvex(const sf::ConvexShape& c1, const sf::ConvexShape& c2);
/*see if two convex shapes intersect one another*/

inline bool ConvexRect(const sf::ConvexShape& c1, const sf::FloatRect& R1);
/*see if a convex shape collides with a Rect*/

inline bool ConvexRadial(const sf::ConvexShape& c1, const sf::Vector2f& p1, float r1);
/*see if a convex shape collides with a circle*/

//polymorphism of collision detection between two sets of objects

//circle-circle
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle1, const std::pair<sf::Vector2f, float>& circle2);

//circle-rect
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle, const sf::FloatRect& rect);
inline bool CollisionDetected(const sf::FloatRect Rect, const std::pair<sf::Vector2f, float> circle);

//circle-line
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle, const std::pair<sf::Vector2f, sf::Vector2f>& line);
inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line, const std::pair<sf::Vector2f, float>& circle);

//circle-convex
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle, const sf::ConvexShape& shape);
inline bool CollisionDetected(const sf::ConvexShape& shape, const std::pair<sf::Vector2f, float>& circle);

//rect-rect
inline bool CollisionDetected(const sf::FloatRect rect1, const sf::FloatRect& rect2);

//rect-line
inline bool CollisionDetected(const sf::FloatRect& rect, const std::pair<sf::Vector2f, sf::Vector2f>& line);
inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line, const sf::FloatRect& rect);

//rect-convex
inline bool CollisionDetected(const sf::FloatRect& rect, const sf::ConvexShape& shape);
inline bool CollisionDetected(const sf::ConvexShape& shape, const sf::FloatRect& rect);

//convex-convex
inline bool CollisionDetected(const sf::ConvexShape& shape1, const sf::ConvexShape& shape2);

//convex-line
inline bool CollisionDetected(const sf::ConvexShape& shape, const std::pair<sf::Vector2f, sf::Vector2f>& line);
inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line, const sf::ConvexShape& shape);

//line-line
inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line1, const std::pair<sf::Vector2f, sf::Vector2f> line2);


inline bool RadialRadial(const sf::Vector2f& p1, float r1, const sf::Vector2f& p2, float r2) {

	return (hypotf(p1.x-p2.x, p1.y-p2.y) < (r1 + r2));
}

inline bool RectRect(const sf::FloatRect& R1, const sf::FloatRect& R2) {
	
	return R1.intersects(R2);
}

inline bool RadialRect(const sf::Vector2f& p1, float r1, const sf::FloatRect& R1) {

	sf::Vector2f A;
	sf::Vector2f B;
	sf::Vector2f C;
	sf::Vector2f D;
	A.x = R1.left; A.y = R1.top;
	B.x = A.x + R1.width; B.y = A.y;
	C.x = B.x; C.y = B.y + R1.height;
	D.x = A.x; D.y = C.y;
	return (RadialLine(p1,r1,A,B) || RadialLine(p1,r1,B,C) || RadialLine(p1,r1,C,D) || RadialLine(p1,r1,D,A));

}

inline bool RadialLine(const sf::Vector2f& p1, float r1, const sf::Vector2f& A, const sf::Vector2f& B) {

	return (abs((B.y-A.y)*p1.x-(B.x-A.x)*p1.y+B.x*A.y-B.y*A.x)/(sqrt(pow((B.y-A.y),2)+pow((B.x-A.x),2))) < r1);
}

inline bool ConvexConvex(const sf::ConvexShape& c1, const sf::ConvexShape& c2) {
/*not complete, using the separation axis theorem*/
	sf::Vector2f axis;
	sf::Vector2f temp;
	sf::Vector2f point;
	float min1, max1, min2, max2, proj;
	for (int i = 0; i < c1.getPointCount() - 1; ++i) {
		temp = c1.getPoint(i) - c1.getPoint(i+1);
		axis.x = temp.y;
		axis.y = -temp.x;
		min1 = 0; max1 = 0;
		for (int j = 0; j < c2.getPointCount() - 1; ++j) {
			point = c2.getPoint(j);
			proj = point.x*axis.x + point.y*axis.y;
			if (proj < min1)
				min1 = proj;
			else if (proj > max1) 
				max1 = proj;
		}
		min2 = 0; max2 = 0;
		for (int j = 0; j < c1.getPointCount() - 1; ++j) {
			point = c1.getPoint(j);
			proj = point.x*axis.x + point.y*axis.y;
			if (proj < min2)
				min2 = proj;
			else if (proj > max2) 
				max2 = proj;
		}
		if (!((min2 < min1 && min1 < max2) || (min1 < min2 && min2 < max1)))
			return false;
	}
	for (int i = 0; i < c2.getPointCount() - 1; ++i) {
		temp = c2.getPoint(i) - c2.getPoint(i+1);
		axis.x = temp.y;
		axis.y = -temp.x;
		min1 = 0; max1 = 0;
		for (int j = 0; j < c2.getPointCount() - 1; ++j) {
			point = c2.getPoint(j);
			proj = point.x*axis.x + point.y*axis.y;
			if (proj < min1)
				min1 = proj;
			else if (proj > max1) 
				max1 = proj;
		}
		min2 = 0; max2 = 0;
		for (int j = 0; j < c1.getPointCount() - 1; ++j) {
			point = c1.getPoint(j);
			proj = point.x*axis.x + point.y*axis.y;
			if (proj < min2)
				min2 = proj;
			else if (proj > max2) 
				max2 = proj;
		}
		if (!((min2 < min1 && min1 < max2) || (min1 < min2 && min2 < max1)))
			return false;
	}	
	return true;
}


//polymorphism of collision detection between two sets of objects

//circle-circle
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle1, const std::pair<sf::Vector2f, float>& circle2){

	return (mag(circle1.first-circle2.first) < (circle1.second+circle2.second));
}

//circle-rect
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle, const sf::FloatRect& rect){ 

	sf::Vector2f points[4];
	points[0].x = rect.left; points[0].y = rect.top;
	points[1].x = points[0].x + rect.width; points[1].y = points[0].y;
	points[2].x = points[1].x; points[2].y = points[1].y + rect.height;
	points[3].x = points[0].x; points[3].y = points[2].y;
	for (int i = 0; i < 4; ++i) {
		if (CollisionDetected(circle, std::pair<sf::Vector2f, sf::Vector2f>(points[i], points[(i+1)%4])))
			return true;
	}
	return false;
}

inline bool CollisionDetected(const sf::FloatRect rect, const std::pair<sf::Vector2f, float> circle){

	return CollisionDetected(circle, rect);
}

//circle-line
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle, const std::pair<sf::Vector2f, sf::Vector2f>& line){ 

	const sf::Vector2f& A = line.first;
	const sf::Vector2f& B = line.second;
	return (abs(cross_prod(circle.first, B-A)+cross_prod(B,A))/(mag(A-B)) < circle.second);
}

inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line, const std::pair<sf::Vector2f, float>& circle){

	return CollisionDetected(circle, line);
}

//circle-convex
inline bool CollisionDetected(const std::pair<sf::Vector2f, float>& circle, const sf::ConvexShape& shape){ }
inline bool CollisionDetected(const sf::ConvexShape& shape, const std::pair<sf::Vector2f, float>& circle){

	return CollisionDetected(circle, shape);
}

//rect-rect
inline bool CollisionDetected(const sf::FloatRect rect1, const sf::FloatRect& rect2){

	return rect1.intersects(rect2);
}

//rect-line
inline bool CollisionDetected(const sf::FloatRect& rect, const std::pair<sf::Vector2f, sf::Vector2f>& line){ }
inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line, const sf::FloatRect& rect){

	return CollisionDetected(rect, line);
}

//rect-convex
inline bool CollisionDetected(const sf::FloatRect& rect, const sf::ConvexShape& shape){ }
inline bool CollisionDetected(const sf::ConvexShape& shape, const sf::FloatRect& rect){

	return CollisionDetected(rect, shape);
}

//convex-convex
inline bool CollisionDetected(const sf::ConvexShape& shape1, const sf::ConvexShape& shape2){  }

//convex-line
inline bool CollisionDetected(const sf::ConvexShape& shape, const std::pair<sf::Vector2f, sf::Vector2f>& line){ }
inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line, const sf::ConvexShape& shape){

	return CollisionDetected(shape, line);
}

//line-line
inline bool CollisionDetected(const std::pair<sf::Vector2f, sf::Vector2f>& line1, const std::pair<sf::Vector2f, sf::Vector2f> line2){ }




class GameAsset;
bool HaveCollided(GameAsset* A, GameAsset* B); //check if any two assets have collided

#endif
