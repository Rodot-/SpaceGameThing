
#ifndef __INTEGRATORS_H__
#define __INTEGRATORS_H__

void RK4_step(float t, float dt, float f_t[], void(*rhs_function)(float t, float f[], float rhsf[], universe* model), universe *model ); 


#endif

