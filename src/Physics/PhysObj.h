#ifndef PHYSOBJ_H
#define PHYSOBJ_H

#include <string>

class physObj {

	public:

		physObj() {}; //constructor

		~physObj() {}; // destructor

		void outputPhysVec() {}; //Print the location and velocity to the console
		virtual void interact(*physObj other) {}; //interact with another physObj

	private:

		float _mass, _mu_k, _mu_s, _k, _beta; //mass, kinetic friction, static_friction, spring constant, damping coefficient
		const unsigned int _ndim = 4; //4 physical dimensions, x, y, vx, vy
		float* _physVec = (float*)malloc(sizeof(float)*_ndim); //Physics vector
		
		float* _com = (float*)malloc(sizeof(float)*_ndim/2); //center of mass

};


#endif
