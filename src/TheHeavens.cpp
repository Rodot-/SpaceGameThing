#include "World/TheHeavens.h"

HeavenlyBody::HeavenlyBody(void) { }

HeavenlyBody::HeavenlyBody(float radius, float mass, DangerLevel risk) {

	_radius = radius;
	this->GetSprite().setScale(_radius, _radius);
	_mass = mass;
	_risk = risk;
}

HeavenlyBody::~HeavenlyBody(void) { }

void HeavenlyBody::SetRadius(float radius) {
	_radius = radius;
	this->GetSprite().setScale(_radius, _radius);
}

float HeavenlyBody::GetRadius() const {
	return _radius;
}

DangerLevel HeavenlyBody::GetDangerLevel() const {
	return _risk;
}



