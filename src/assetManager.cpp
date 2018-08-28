#include "World/assetManager.h"
#include "World/Forces.h"
#include <iostream>

//base asset manager
AssetManager::AssetManager(void) {}

AssetManager::~AssetManager(void) {
	std::for_each(_gameAssets.begin(), _gameAssets.end(), GameAssetDeallocator());
}

void AssetManager::Add(std::string name, GameAsset* gameAsset) {
	_gameAssets.insert(std::pair<std::string, GameAsset*>(name, gameAsset));
}

void AssetManager::Remove(std::string name) {
	std::map<std::string, GameAsset*>::iterator results = _gameAssets.find(name);
	if(results != _gameAssets.end() )
	{
		delete results->second;
		_gameAssets.erase(results);
	}
}

int AssetManager::GetObjectCount(void) const {
	return _gameAssets.size();
}

GameAsset* AssetManager::Get(std::string name) const {
	std::map<std::string, GameAsset*>::const_iterator results = _gameAssets.find(name);
	if (results == _gameAssets.end() )
		return NULL;
	return results->second;
}


void AssetManager::DrawAll(sf::RenderWindow& window) {
	std::map<std::string, GameAsset*>::const_iterator itr = _gameAssets.begin();
	sf::Vector2i world_r;
	sf::Vector2f asset_r;
	while (itr != _gameAssets.end()) {
		asset_r = itr->second->GetPosition();
		world_r = window.mapCoordsToPixel(asset_r); //objects need to be drawn at integer coodinates
		itr->second->SetPosition(world_r.x, world_r.y);
		itr->second->Draw(window);
		itr->second->SetPosition(asset_r.x, asset_r.y); //set the position back to it's float coordinate
		itr++;
	}
}

void AssetManager::UpdateAll(float elapsedTime) {

	std::map<std::string, GameAsset*>::const_iterator itr = _gameAssets.begin();
	for (itr; itr != _gameAssets.end(); ++itr) {
		itr->second->Update(elapsedTime);
	}
}


//Physics Manager
PhysicsManager::PhysicsManager(void) {

	_integrator = &RK4_step;
	//_integrator = &Euler_step;
}

PhysicsManager::~PhysicsManager(void) {}

void PhysicsManager::Add(PhysicalAsset* physObj) {
	_physicsAssets.push_back(physObj);	
}

void PhysicsManager::Remove(int pos) {
	_physicsAssets.erase(_physicsAssets.begin()+pos);
}

void PhysicsManager::SetWorld(WorldGeometry* world) {

	_world = world;
}

void PhysicsManager::InitPhysVec(void) {

	_physVec = (float*)malloc(sizeof(float)*_ndim*_physicsAssets.size());
	for (int i = 0; i < _physicsAssets.size() ; ++i) {
		for (int j = 0; j < 6; ++j) {
			_physVec[6*i+j] = _physicsAssets[i]->getPhysVec()[j];
		}
		_physicsAssets[i]->setPhysVec(&_physVec[6*i]);
	}

}
void PhysicsManager::UpdatePhysics(float elapsedTime) {
	//Test using the universe physics
	_integrator(0, elapsedTime, _physVec, _physicsAssets, _world, surfaceRHSF);
	for (std::vector<PhysicalAsset*>::iterator i = _physicsAssets.begin(); i < _physicsAssets.end(); ++i) {
		(*i)->PhysUpdate(elapsedTime);
	} 
	ProcessCollisions();

}

void PhysicsManager::ProcessCollisions(void) {

	std::vector<PhysicalAsset*>::iterator itr = _physicsAssets.begin();
	
	for (itr; itr != _physicsAssets.end(); ++itr) {

		if (_world->HasCollided(*itr))
			_world->ManageCollision(*itr);
	}
}

int PhysicsManager::GetObjectCount(void) const {
	return _physicsAssets.size();
}

//Universe Physics Manager

UniversePhysicsManager::UniversePhysicsManager(Universe* universe) {
	_universe = universe;
 }

UniversePhysicsManager::~UniversePhysicsManager(void) { }

void UniversePhysicsManager::UpdatePhysics(float elapsedTime) {}



