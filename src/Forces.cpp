
#include <cmath>
#include "World/Forces.h"
#include "World/Worlds.h"
#include "stdlib.h"
#include <stdio.h>

#define G -100

void basicRHSF(float t, float f[], float rhsf[], PhysicalAsset* physObj) {

	rhsf[0] = f[2]; //Velocity X
	rhsf[1] = f[3]; //Velocity Y
	rhsf[4] = f[5]; //Angular Velocity

}

float* gravityVector(PhysicalAsset* objA, PhysicalAsset* objB) {

	float* force = (float*)malloc(sizeof(float)*2);	
	float dx, dy, r, M, r3;

	dx = objA->getPhysVec()[0] - objB->getPhysVec()[0];
	dy = objA->getPhysVec()[1] - objB->getPhysVec()[1];

	r = hypotf(dx, dy);
	r3 = r*r*r;
	M = objA->getMass() * objB->getMass();
	force[0] = G*M/(r3)*dx;
	force[1] = G*M/(r3)*dy;

	return force;
}

void gravitationalRHSF(float t, float f[], float rhsf[], std::vector<PhysicalAsset*> physVec) {

	float* Fg;
	for (int i = 0; i < physVec.size()*6; ++i) {
		rhsf[i] = 0;
	}
	for (int i = 0; i < physVec.size(); ++i) {
		rhsf[6*i] = f[6*i+2];
		rhsf[6*i+1] = f[6*i+3];
		rhsf[6*i+4] = f[6*i+5];
		for (int j = i+1; j < physVec.size(); ++j) {
			Fg = gravityVector(physVec[i], physVec[j]);

			rhsf[6*i+2] += Fg[0]/physVec[i]->getMass();
			rhsf[6*i+3] += Fg[1]/physVec[i]->getMass();

			rhsf[6*j+2] -= Fg[0]/physVec[j]->getMass();
			rhsf[6*j+3] -= Fg[1]/physVec[j]->getMass();
			delete Fg;
		}
	}	

}