#ifndef PHYSICS_H
#define PHYSICS_H

typedef enum {RADIAL, RECT, CONVEX} HBType; //type of hitbox

typedef struct { //possibly recursive container of some hitbox attributes

	HBType type; //type of hitbox
	int size;
	float* params; /*array of hitbox params
	one of the following
	- length 3 array of (x, y, radius)
	- length 6 array of (x, y, top, left, height, width) (top and left are constant.  x, y are offests)
	- length 2+2xN array of N > 2 points on a convex polygon with the first being a dynamic offset.
	*/
	void* refined_hitBox; //optional smaller more precise hitbox

} hitBox;

typedef struct { //container of physics parameters for a physics object

	float x, y, theta, px, py, L; //physics vector components
	float com_x, com_y; //center of mass components
	float m; //mass
	float k; //spring constant
	float r0; //spring equilibrium distance
	float b; //damping
	float mu_s; //static friction
	float mu_k; //kinetic friction
	float I; //moment of inertia
	float C; //Drag coefficient
	float A; //cross-sectional area

} physicsParams;

typedef struct { //container of world physics parameters

	const float G; //Gravitational constant
	const float k; //Boltzman Constant
	const float h; //Planck's constant
	const float mu_0; //magnetic permiability of free space
	const float e_0; //electric permiability of free space
	const float c; //speed of light (1/sqrt(mu_0 * e_0))
	float g; //acceleration due to gravity at some point
	float rho; //Air density
	float P; //Air pressure
	float T; //Air temperature
	float c_s; //sound speed

} worldParams;

typedef struct { //a basic 2D vector container for convienience

	float x, y;
} vec2D;

typedef struct { //contains basic information about a collision

	unsigned char detection; //logical, was a collision detected?
	float x, y; //point of collision
	float size; //size of the projection overlaps
	vec2D MTV; //minimum translation vector

} collisionResult;

#ifdef __cplusplus
	extern "C" {
		//two body interactions
		vec2D Gravity(const physicsParams& obj1, const physicsParams& obj2, const worldParams& world); //2 body gravity
		vec2D Spring(const physicsParams& obj1, const physicsParams& obj2, const worldParams& world); //spring interaction

		//one body interactions
		vec2D gravity(const physicsParams& obj, const worldParams& world); //scalar gravity 
		vec2D Drag(const physicsParams& obj, const worldParams& world); //drag force
		vec2D Friction(const physicsParams& obj, const worldParams& world); //friction force

	};
#endif /* __cplusplus */

#endif /*PHYSICS_H*/
