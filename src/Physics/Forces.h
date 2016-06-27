#ifndef FORCES_H
#define FORCES_H

#include <cmath>
#include <vector>
#include <string>
#include "Math/integrators.h"

//module for defining forces acting between physics objects


class physObj; //so we at least have an instance of it

float* Gravity(physObj* objA, physObj* objB);
float* Friction(physObj* objA, physObj* objB);
float* Spring(physObj* objA, physObj* objB);

float* ScalarField(physObj* objA, physObj* objB, std::vector<float> field); //could replace std::vector with some world like object

#endif

