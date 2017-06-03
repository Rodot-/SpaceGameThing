#ifndef FORCES_H
#define FORCES_H

#include <cmath>
#include <vector>
#include <string>
#include "gameAssets.h"
#include "WorldGeometry.h"

//module for defining forces acting between physics objects

//typedef (void)(*RHSF)(float, float*, float*, std::vector<PhysicalAsset*>);

float* gravityVector(PhysicalAsset* objA, PhysicalAsset* objB);

void gravitationalRHSF(float t, float f[], float rhsf[], std::vector<PhysicalAsset*>, WorldGeometry* world);

void surfaceRHSF(float t, float f[], float rhsf[], std::vector<PhysicalAsset*> physVec, WorldGeometry* world);

float* Gravity(PhysicalAsset* objA, PhysicalAsset* objB);
float* SurfaceGravity(PhysicalAsset* obj);
float* Friction(PhysicalAsset* objA, PhysicalAsset* objB);
float* Spring(PhysicalAsset* objA, PhysicalAsset* objB);

#endif

