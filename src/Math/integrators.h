
#ifndef __INTEGRATORS_H__
#define __INTEGRATORS_H__

#include "../World/gameAssets.h"
#include <string.h>	
#include <stdio.h>

void RK4_step(float t, float dt, PhysicalAsset* physObj, void(*rhs_function)(float t, float f[], float rhsf[], PhysicalAsset* physObj)); 

void RK4_step(float t, float dt, float f_t[], std::vector<PhysicalAsset*> physVec, void(*rhs_function)(float t, float f[], float rhsf[], std::vector<PhysicalAsset*> physVec)); 

//void RK4_step(float t, float dt, float f_t[], void(*rhs_function)(float t, float f[], float rhsf[], universe* model), universe* model); 


void Euler_step(float t, float dt, float f_t[], void(*rhs_function)(float t, float f[], float rhsf[], PhysicalAsset* physObj), PhysicalAsset* physObj) ;
/*
void Midpoint_step(float t, float dt, float f_t[], void(*rhs_function)(float t, float f[], float rhsf[], params *model), params *model ) ;

*/
#endif

