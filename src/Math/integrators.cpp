#include "integrators.h"


void RK4_step(float t, float dt, float f_t[], void(*rhs_function)(float t, float f[], float rhsf[], universe* model), universe *model ) {

	//float* f_t = &model->vec[0]; 
	float f_f[ndim];
	float rhsf[ndim];
	float f_k[ndim];
	float k, h, s, z;
	int i, j;

	std::memcpy(f_k, f_t, sizeof(float)*ndim );
	std::memcpy(f_f, f_t, sizeof(float)*ndim );

	for (j=0; j<4; ++j) {
		h = ((j + 1) / 2)*0.5;
		s = ((j + 2) / 2)*0.5;
		z = -0.25*j*(j-3)+0.5;
		rhs_function(t + h * dt, f_k, rhsf, model);
		for (i=0; i<ndim; ++i) {
			k = dt * rhsf[i];
			f_k[i] = f_t[i] + s * k;
			f_f[i] += k*z/3.0;
		}
	}
	std::memcpy(f_t, f_f, sizeof(float)*ndim );

}
	
	
