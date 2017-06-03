
#ifndef __INTEGRATORS_H__
#define __INTEGRATORS_H__

#include "../World/gameAssets.h"
#include "../World/WorldGeometry.h"
#include <string.h>	
#include <stdio.h>

typedef void(*integrator)(float, float, float*, std::vector<PhysicalAsset*>, WorldGeometry*, void(*rhs_function)(float, float*, float*, std::vector<PhysicalAsset*>, WorldGeometry*));

//void RK4_step(float t, float dt, PhysicalAsset* physObj, void(*rhs_function)(float t, float f[], float rhsf[], PhysicalAsset* physObj)); 

void RK4_step(float t, float dt, float f_t[], std::vector<PhysicalAsset*> physVec, WorldGeometry* world, void(*rhs_function)(float t, float f[], float rhsf[], std::vector<PhysicalAsset*> physVec, WorldGeometry* world)); 

//void RK4_step(float t, float dt, float f_t[], void(*rhs_function)(float t, float f[], float rhsf[], universe* model), universe* model); 


void Euler_step(float t, float dt, float f_t[], std::vector<PhysicalAsset*> physVec, WorldGeometry* Worlds, void(*rhs_function)(float t, float f[], float rhsf[], std::vector<PhysicalAsset*> physVec, WorldGeometry* world)); 
/*
void Midpoint_step(float t, float dt, float f_t[], void(*rhs_function)(float t, float f[], float rhsf[], params *model), params *model ) ;

*/
#endif

