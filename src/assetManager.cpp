#include "World/assetManager.h"
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
	while (itr != _gameAssets.end()) {
		itr->second->Draw(window);
		itr++;
	}
}


//Physics Manager
PhysicsManager::PhysicsManager(void) {
}

PhysicsManager::~PhysicsManager(void) {}

void PhysicsManager::Add(PhysicalAsset* physObj) {
	_physicsAssets.push_back(physObj);	
}

void PhysicsManager::Remove(int pos) {
	_physicsAssets.erase(_physicsAssets.begin()+pos);
}

void PhysicsManager::UpdatePhysics(void) {

}

int PhysicsManager::GetObjectCount(void) const {
	return _physicsAssets.size();
}

//Universe Physics Manager

UniversePhysicsManager::UniversePhysicsManager(Universe* universe) {
	_universe = universe;
 }

UniversePhysicsManager::~UniversePhysicsManager(void) { }

void UniversePhysicsManager::UpdatePhysics(void) {}



