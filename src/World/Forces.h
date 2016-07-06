#ifndef FORCES_H
#define FORCES_H

#include <cmath>
#include <vector>
#include <string>
#include "gameAssets.h"

//module for defining forces acting between physics objects

void basicRHSF(float t, float f[], float rhsf[], PhysicalAsset* physObj); 

float* Gravity(PhysicalAsset* objA, PhysicalAsset* objB);
float* Friction(PhysicalAsset* objA, PhysicalAsset* objB);
float* Spring(PhysicalAsset* objA, PhysicalAsset* objB);

float* VectorField(PhysicalAsset* objA, PhysicalAsset* objB, sf::Vector2f field); //could replace std::vector with some world like object

#endif

