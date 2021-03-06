#include "World/TheHeavens.h"
#include <cmath>

HeavenlyBody::HeavenlyBody(void) { }

HeavenlyBody::HeavenlyBody(float radius, float mass, DangerLevel risk) {

	_radius = radius;
	_sprite.setScale(_radius, _radius);
	_mass = mass;
	_I = 0.4*_mass*_radius*_radius;
	_risk = risk;
	_collisionMethod = collision::RADIAL;
	_collidable = true;
}

void HeavenlyBody::Load(std::string filename) {

	GameAsset::Load(filename);
	sf::FloatRect bounds = GetLocalBounds();
	SetOrigin(bounds.width/2, bounds.height/2);
	setCOM(bounds.width/2, bounds.height/2); //this has to be relative to the size of the object
}

HeavenlyBody::~HeavenlyBody(void) { }

void HeavenlyBody::SetRadius(float radius) {
	_radius = radius;
	this->GetSprite().setScale(_radius, _radius);
}

float HeavenlyBody::GetRadius() const {
	return _radius*GetLocalBounds().width/2;
}

DangerLevel HeavenlyBody::GetDangerLevel() const {
	return _risk;
}


void HeavenlyBody::BindToHost(HeavenlyBody& other, float radius) {

	sf::Vector2f relativeV = other.GetVelocity();
	float mag = sqrt(100*other.getMass()/radius);
	SetPosition(other.getPhysVec()[0] - radius, other.getPhysVec()[1]);
	setVy(mag+relativeV.y);
	setVx(relativeV.x);

}


