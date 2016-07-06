
#include <cmath>
#include "World/Forces.h"
#include "World/Worlds.h"
#include "stdlib.h"

void basicRHSF(float t, float f[], float rhsf[], PhysicalAsset* physObj) {

	rhsf[0] = f[2]; //Velocity X
	rhsf[1] = f[3]; //Velocity Y
	rhsf[4] = f[5]; //Angular Velocity

}
