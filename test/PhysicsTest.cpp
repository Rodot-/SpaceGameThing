#include <stdio.h>
#include <stdlib.h>
#include "../Physics/Physics.h"
#include <math.h>

#define N 10
#define MAX(x,y) ( (x < y) ? y : x )
#define MIN(x,y) ( (x < y) ? x : y )

/*Physics Pipeline:

	All physics units should be in SI units, conversions to pixels will take place at drawing time

	Take a step with integrator
		Apply each force one by one in any order unless force assigns rather than modified an rhsf value
		if not, any forces that depend on the value of other forces should be places at the end.
		For example, static friction overcoming other outside forces

		Might be easier to just derive a single set of diff eqs using the Lagrangian.  
		Non-conservative forces need a little extra work though

		Forces between objects should also be worked out
		Forces and reference frames too

	Make all corrections
		anything that directly modifies a physicsParam attribute
		I.e. out of bounds, friction stopping cutoff
	Collision detection might be it's own step, need to see.  If anything, it goes at the end
		Detect collision
		Find point of collision
			Find best points
			Find incident and reference edges from best points
			Three step clip to find contact point(s)
				convert pair of contact points to single point if necessary
		//Back up simulation to just before collision (binary search)
			or Move objects back along MTV
		compute result from formula
		//Bring Simulation back up to speed

*/

void Euler_Step(float t, float dt, physicsParams pp[], const worldParams& world, void(*rhsf_function)(float t, physicsParams pp[], float rhsf[], const worldParams& world)) {

	size_t ndim = N*6;
	float rhsf[ndim];
	rhsf_function(t, pp, rhsf, world);
	float* f;
	for (int i = 0; i < N; ++i) {
		f = &(pp[i].x);
		for (int j = 0; j < 6; ++j) {
			f[j] += rhsf[i*6+j]*dt/pp[i].m;
		}
	}
}

inline vec2D Projection(const hitBox& h, const vec2D* axis) {

	vec2D* itr;
	vec2D* begin = (vec2D*)h.params;
	vec2D* end = begin+h.size;
	float min, max, proj;
	min = axis->x*begin->x+axis->y*begin->y;
	max = min;
	for (itr = begin; itr != end; ++itr) {
		proj = itr->x*axis->x+itr->y*axis->y;
		if (proj < min)
			min = proj;
		else if (proj > max)
			max = proj;	
	}
	printf("(%f, %f)\n", min, max);
	return {min, max};
}

inline bool overlaps(const vec2D& p1, const vec2D& p2) {

	return ((p1.x < p2.y && p1.x > p2.x) || 
	(p2.x < p1.y && p2.x > p1.x) || 
	(p1.y > p2.x && p1.y < p2.y) ||
	(p2.y > p1.x && p2.y < p1.y) );
}

collisionResult SeparatingAxisTheorem(const hitBox& h1, const hitBox& h2) {

	vec2D ax;
	vec2D* itr;
	vec2D* begin;
	vec2D* end;
	const hitBox* boxes[2] = {&h1, &h2};
	float size;
	collisionResult result;
	result.detection = 0;
	result.size = 10000; //a large number
	int i;
	int index;

	for (i = 0; i < 2; ++i) {
		begin = (vec2D*)boxes[i]->params;
		end = begin+boxes[i]->size;
		for (itr = begin; itr != end; ++itr) {
			if (itr == end-1) //make sure we go back to the first point at the end
				index = -boxes[i]->size + 1;
			else
				index = 1;
			ax.x = itr[index].y-itr[0].y;
			ax.y = itr[0].x-itr[index].x;
			printf("axis = (%f, %f)\n", ax.x, ax.y);
			printf("n = (%f, %f)\n", ax.y, -ax.x);
			vec2D proj1 = Projection(h1, &ax);
			vec2D proj2 = Projection(h2, &ax);
			if (!overlaps(proj1, proj2))
				return result; //instead of this, check to see if they *will* collide before returning
			else {
				size = MIN((proj1.y), (proj2.y)) - MAX((proj1.x), (proj2.x));	
				if (size < result.size) {
					result.size = size;
					result.x = MAX(proj1.x, proj2.x);
					result.y = MIN(proj1.y, proj2.y);
					result.MTV = ax;
				}
			}
		}
	}
	result.detection = 1;
	float mag = hypotf(result.MTV.x, result.MTV.y); //normalize the MTV axis
	result.MTV.x /= mag;
	result.MTV.y /= mag;
	return result;

	/*
	You'd want to move one of the objects in the direction of 'MTV' with a distance of 'size'
	Finding 'p' (collision point) still needs to be worked out
		It can probably be worked out from 'MTV' and 'size' at least along the 'MTV' axis
		* 'x' and 'y' will allow us to figure out which points are close to 'p'
		'p' = pointof('x') + 'size'*n-hat
	*/
}


void basicRHSF(float t, physicsParams f[], float rhsf[], const worldParams& world) {

	int i;
	for (i = 0; i < N; ++i) {
		rhsf[i*6+0] = f[i].px;
		rhsf[i*6+1] = f[i].py;
		rhsf[i*6+2] = f[i].L;
		rhsf[i*6+3] = 0.0;
		rhsf[i*6+4] = 0.0;
		rhsf[i*6+5] = 0.0;

		if ((f[i].y <= 0) && (fabs(rhsf[i*6+0]) > 0)) {
			vec2D fric = Friction(f[i], world);
			if (fabs(rhsf[i*6+0])/0.01 < fabs(fric.x)) {
				rhsf[i*6+0] = 0.0;
			}
			else {
				rhsf[i*6+3] += fric.x;
				rhsf[i*6+4] += fric.y;
			}
		}
		if (f[i].y > 0) {
			vec2D grav = gravity(f[i], world);
			rhsf[i*6+3] += grav.x;
			rhsf[i*6+4] += grav.y;
		}
		else {
			if (f[i].py < 2*f[i].m*world.g*0.01) {
				f[i].py *= -0.6;
			}
			f[i].y = 0;
		}	
	}
}

int main(void) {


	hitBox h1, h2;
	h1.size = 4;
	h2.size = 3;

	h1.params = (float*)malloc(sizeof(float)*8);
	h1.params[0] = 1.0;
	h1.params[1] = 2.0;

	h1.params[2] = 2.0;
	h1.params[3] = 5.0;

	h1.params[4] = 5.0;
	h1.params[5] = 3.0;

	h1.params[6] = 3.0;
	h1.params[7] = 1.0;

	h2.params = (float*)malloc(sizeof(float)*6);
	h2.params[0] = 4.0;
	h2.params[1] = 3.0;

	h2.params[2] = 4.5;
	h2.params[3] = 7.0;

	h2.params[4] = 6.0;
	h2.params[5] = 6.0;

	collisionResult result = SeparatingAxisTheorem(h1, h2);
	printf("%i %f %f %f %f %f\n",result.detection, result.x, result.y, result.size, result.MTV.x, result.MTV.y);


	/*
	physicsParams p[N];
	for (int i = 0; i < N; ++i) {
		p[i] = {(float)(i*2.0), 5, 0, (float)(i*0.1), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1e-2, 0.6, 0.4, 0.0, 0.24, 1.0};
	}
	worldParams world = {1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 9.8, 0.1, 0.0, 0.0, 0.0};	
		
	float t, dt;
	t = 0.0;
	dt = 0.01;	
	for (int i = 0; i < 1000; ++i) {
		Euler_Step(t, dt, p, world, basicRHSF);
		t += dt;
		printf("%f ", t);
		for (int j=0; j < N; ++j) {
			printf("%f %f ", p[j].x, p[j].y); 
		}
		printf("\n");
	}
	*/

	return 0;
}

