
#include "World/WorldGeometry.h"
#include "Debug/Debug.h"

WorldGeometry::WorldGeometry(void) {}

WorldGeometry::~WorldGeometry(void) {}

void WorldGeometry::Load(std::string filename) {
	printd("About to load\n");
	CompoundAsset::Load(filename);
}


