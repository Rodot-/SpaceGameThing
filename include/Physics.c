//All physics forces and basic container managment
#include "Physics/Physics.h"
#include <math.h>

vec2D Gravity(const physicsParams& obj1, const physicsParams& obj2, const worldParams& world) {

	vec2D dr;
	float R, F0;
	dr.x = obj2.x - obj1.x;
	dr.y = obj2.y - obj1.y; 
	R = hypotf(dr.x, dr.y);
	F0 = obj1.m*obj2.m*world.G/(R*R*R);
	return {F0*dr.x, F0*dr.y};	
}

vec2D Spring(const physicsParams& obj1, const physicsParams& obj2, const worldParams& world) {

	vec2D dr;
	float R, F0;
	dr.x = obj2.x - obj1.x;
	dr.y = obj2.y - obj2.y;
	R = hypotf(dr.x, dr.y);
	F0 = -obj2.k*(1.0 - obj2.r0/R);
	return {F0*dr.x, F0*dr.y};
}

vec2D gravity(const physicsParams& obj, const worldParams& world) {

	return {0.0, -world.g};
}

vec2D Drag(const physicsParams& obj, const worldParams& world) {

	vec2D v;
	float F0, V;
	v.x = obj.px/obj.m;
	v.y = obj.py/obj.m;
	V = hypotf(v.x, v.y);
	F0 = -0.5*world.rho*V*obj.C*obj.A;
	return {v.x*F0, v.y*F0};
}

vec2D Friction(const physicsParams& obj, const worldParams& world) {
	
	float F0;
	F0 = obj.m*world.g*obj.mu_k;
	F0 *= (obj.px > 0) ? -1.0 : 1.0;
	return {F0, 0.0};
}


