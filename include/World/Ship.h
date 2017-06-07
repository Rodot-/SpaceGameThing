//file for defining parts of a ship as well as the ship itself
#ifndef SHIP_H
#define SHIP_H

#include "gameAssetis.h"


class ShipPart : public DynamicAsset { //TODO: possibly have these classes contain a generic struct for managing the level of some resource whether it is HP, fuel, ammo, etc.

	public:

		ShipPart();
		~ShipPart();

		float GetHP() const;
		void SetHP(float HP);

		float GetMaxHP() const;
		void SetMaxHP(float HP);

		float TakeDamage(float damage);

	private:

		float _HP, _maxHP;
};


class FuelTank : public ShipPart {

	public:

		FuelTank();
		~FuelTank();

		float GetFuelLevel() const;
		void SetFuelLevel(float fuel);

		float GetMaxFuelLevel() const;
		void SetMaxFuelLevel(float maxFuel);

		float Drain

	private:

		float _fuel, _totalFuel;

};

class Ship : public CompoundAsset {

	public:

		Ship();
		~Ship();
	
		Interact(sf::Event event);
		Update(float elapsedTime);


};

ShipPart& Hull(void) {

	ShipPart* hull = new ShipPart();
	hull->Load("../bin/ship/body.png");
	return *hull;
};

ShipPart& Cockpit(void) {

	ShipPart* cockpit = new ShipPart();
	cockpit->Load("../bin/ship/cockpit.png");
	return *cockpit;
};

ShipPart& Boosters(void) {

	ShipPart* boosters = new ShipPart();
	boosters->Load("../bin/ship/boosters.png");
	return *boosters;
};

ShipPart& Guns(void) {

	ShipPart* guns = new ShipPart();
	guns->Load("../bin/ship/guns.png");
	return *guns;
};

ShipPart& Mainpropulsion(void) {

	ShipPart* mainpropulsion = new ShipPart();
	mainpropulsion->Load("../bin/ship/mainpropulsion.png");
	return *mainpropulsion;
};

Ship* GetShip(void) {

	Ship* ship = new Ship();
	ship->Load("");
	ship->Add("engine", Mainpropulsion(), sf::Vector2f(0.0f,0.0f));
	ship->Add("boosters", Boosters(), sf::Vector2f(0.0f,0.0f));
	ship->Add("guns", Guns(), sf::Vector2f(0.0f,0.0f));
	ship->Add("cockpit", Cockpit(), sf::Vector2f(0.0f,0.0f));	
	ship->Add("hull", Hull(), sf::Vector2f(0.0f,0.0f));	
	ship->setMass(10.0);
	ship->SetScale(0.5,0.5);
	return ship;
};	



#endif
