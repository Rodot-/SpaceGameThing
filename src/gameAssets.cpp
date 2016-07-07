
#include "World/gameAssets.h"
#include "World/Forces.h"
#include "Math/integrators.h"
#include <stdio.h>


//General Game asset
GameAsset::GameAsset(void) : _isLoaded(false), _collidable(false) {
}

GameAsset::~GameAsset(void) {}

void GameAsset::Load(std::string filename) {

	if (_texture.loadFromFile(filename) == false) {
		_filename = "";
		_isLoaded = false;
	}
	else {
		_filename = filename;
		_sprite.setTexture(_texture);
		_isLoaded = true;
	}
}

void GameAsset::Draw(sf::RenderWindow& window) {
	if (_isLoaded) window.draw(_sprite);
}

void GameAsset::Update(float elapsedTime) {}

sf::FloatRect GameAsset::GetLocalBounds(void) const {

	return _sprite.getLocalBounds();
} 

void GameAsset::SetPosition(float x, float y) {
	if (_isLoaded) _sprite.setPosition(x, y);
}

void GameAsset::SetColor(const sf::Color& color) {

	_sprite.setColor(color);
}

void GameAsset::SetOrigin(float x, float y) {
	
	_sprite.setOrigin(x, y);
}

sf::Vector2f GameAsset::GetPosition(void) const {
	return _sprite.getPosition();
}

bool GameAsset::SetCollidable(bool state) { 
	_collidable = state;
}

sf::Sprite& GameAsset::GetSprite(void) {
	return _sprite;
}


bool GameAsset::IsLoaded(void) const {
	return _isLoaded;
}

bool GameAsset::IsCollidable(void) const {
	return _collidable;
}

//Physical Assets (Physics Objects)
PhysicalAsset::PhysicalAsset(void) {
	_physVec = (float*)malloc(sizeof(float)*_ndim);
	for (int i = 0; i < _ndim; ++i) {
		_physVec[i] = 0.0f;
	}
	_COM = (float*)malloc(sizeof(float)*2);
}

PhysicalAsset::~PhysicalAsset(void) {}

void PhysicalAsset::Update(float elapsedTime) {

	/*
	float* rhsf = (float*)malloc(sizeof(float)*_ndim);
	Euler_step(0, elapsedTime, _physVec, basicRHSF, this);
	SetPosition(_physVec[0], _physVec[1]);
	GetSprite().setRotation(_physVec[4]);
	*/
	SetPosition(_physVec[0], _physVec[1]);
	GetSprite().setRotation(_physVec[4]);
}

void PhysicalAsset::Draw(sf::RenderWindow& window) {
	GameAsset::Draw(window);
}


sf::Vector2f PhysicalAsset::GetVelocity(void) { 
	_velocity.x = _physVec[2];
	_velocity.y = _physVec[3];
	return _velocity;
}

float PhysicalAsset::GetOmega() const { return _physVec[5]; }
float PhysicalAsset::GetTheta() const { return _physVec[4]; }

float PhysicalAsset::getMass() const { return _mass; }
float PhysicalAsset::getMu_k() const { return _mu_k; }
float PhysicalAsset::getMu_s() const { return _mu_s; }
float PhysicalAsset::getK() const { return _k; }
float PhysicalAsset::getBeta() const { return _beta; }
float PhysicalAsset::getI() const { return _I; }
float* PhysicalAsset::getCOM() const { return _COM; }
float* PhysicalAsset::getPhysVec() const { return _physVec; }

void PhysicalAsset::SetPosition(float x, float y) {

	GameAsset::SetPosition(x, y);
	_physVec[0] = x;
	_physVec[1] =y;
}

void PhysicalAsset::setMass(float mass) { _mass = mass; }
void PhysicalAsset::setMu_k(float mu_k) { _mu_k = mu_k; }
void PhysicalAsset::setMu_s(float mu_s) { _mu_s = mu_s; }
void PhysicalAsset::setK(float k) { _k = k; }
void PhysicalAsset::setBeta(float beta) { _beta = beta; }
void PhysicalAsset::setI(float I) { _I = I; }
void PhysicalAsset::setX(float x) { _physVec[0] = x; }
void PhysicalAsset::setY(float y) { _physVec[1] = y; }
void PhysicalAsset::setVx(float vx) { _physVec[2] = vx; }
void PhysicalAsset::setVy(float vy) { _physVec[3] = vy; }
void PhysicalAsset::setTheta(float theta) { _physVec[4] = theta; }
void PhysicalAsset::setOmega(float omega) { _physVec[5] = omega; }
void PhysicalAsset::setCOM(float x, float y) { _COM[0] = x; _COM[1] = y; }
void PhysicalAsset::setPhysVec(float* vec) {
	delete _physVec;
	_physVec = vec;
}




