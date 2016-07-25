//library of boolean fucntions for determining collisions from various types

#ifndef COLLISION_H
#define COLLISION_H

#include "SFML/Graphics.hpp"
#include "../World/gameAssets.h"
#include <cmath>

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

bool HaveCollided(GameAsset* A, GameAsset* B); //check if any two assets have collided

#endif
