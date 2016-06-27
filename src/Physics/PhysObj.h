#ifndef PHYSOBJ_H
#define PHYSOBJ_H

#include <string>

class physObj {

	public:

		physObj() {}; //constructor

		~physObj() {}; // destructor

		void outputPhysVec() {}; //Print the location and velocity to the console
		
		//getters
		float getMass() const;
		float getMu_k() const;
		float getMu_s() const;
		float getK() const;
		float getBeta() const;
		float getI() const;
		float getX() const;
		float getY() const;
		float getVx() const;
		float getVy() const;
		float getTheta() const;
		float getOmega() const;
		float* getCOM() const;
		float* getPhysVec() const;

		//setters
		void setMass(float mass);
		void setMu_k(float mu_k);
		void setMu_s(float mu_s);
		void setK(float k);
		void setBeta(float beta);
		void setI(float I);
		void setX(float x);
		void setY(float y);
		void setVx(float vx);
		void setVy(float vy);
		void setTheta(float theta);
		void setOmega(float omega);
		void setCOM(float x, float y);
		void updatePhysVec(float* newPhysVec);

		virtual void interact(*physObj other) {}; //interact with another physObj

	private:

		float _mass, _mu_k, _mu_s, _k, _beta, _I; //mass, kinetic friction, static_friction, spring constant, damping coefficient, moment of inertia
		const unsigned int _ndim = 6; //6 physical dimensions, x, y, vx, vy, theta, omega
		float* _physVec = (float*)malloc(sizeof(float)*_ndim); //Physics vector
		
		float* _COM = (float*)malloc(sizeof(float)*2); //center of mass

};


#endif
