#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <sstream>
#include "World/gameAssets.h"
#include "World/assetManager.h"
#include "World/TheHeavens.h"
#include "Accounting/Registries.h"
#include "Math/QuadTree.h"
#include "Math/Collision.h"
#include "World/HitBox.h"

#define WIDTH 1920/2
#define HEIGHT 1080/2
#define FPS 60.0


int main(int argc, char* argv[]) {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SpaceGameThing");
	sf::Clock clock;
	sf::Clock physClock;

	float dt;

	HeavenlyBody* planet = new HeavenlyBody(0.25, 25000, QUIET);
	planet->Load("../bin/planet.png");
	planet->SetPosition(WIDTH/2, 95);
	planet->SetCollidable(true);
	//planet->SetOrigin(95,95);
	planet->SetColor(sf::Color(255, 0, 0, 255));
	HitBoxBase<std::pair<sf::Vector2f, float> > hbox(std::pair<sf::Vector2f, float>(sf::Vector2f(95, 95), planet->GetRadius()));
	planet->SetHitBox((void*)(&hbox), collision::RADIAL);

	HeavenlyBody* planet2 = new HeavenlyBody(2.0, 200000, QUIET);
	planet2->Load("../bin/planet.png");
	planet2->SetPosition(WIDTH/2, HEIGHT+90);
	planet2->SetCollidable(true);
	//planet2->SetOrigin(95,95);
	planet2->SetColor(sf::Color(255, 0, 0, 255));
	HitBoxBase<std::pair<sf::Vector2f, float> > hbox2(std::pair<sf::Vector2f, float>(sf::Vector2f(95, 95), planet2->GetRadius()));
	planet2->SetHitBox((void*)(&hbox2), collision::RADIAL);


	HeavenlyBody* planet3 = new HeavenlyBody(0.5, 20000, QUIET);
	planet3->Load("../bin/planet.png");
	planet3->SetPosition(WIDTH/4, 90);
	planet3->SetCollidable(true);
	//planet3->SetOrigin(95,95);
	planet3->SetColor(sf::Color(255, 0, 0, 255));
	HitBoxBase<std::pair<sf::Vector2f, float> > hbox3(std::pair<sf::Vector2f, float>(sf::Vector2f(95, 95), planet3->GetRadius()));
	planet3->SetHitBox((void*)(&hbox3), collision::RADIAL);



	//test a compound asset
	CompoundAsset* cst = new CompoundAsset();
	cst->Load("../bin/scripts/assets/test.ass");
	cst->SetOrigin(256, 256);
	cst->SetPosition(WIDTH/2, HEIGHT/2);
	cst->setMass(100000.0);
	cst->SetScale(0.25, 0.25);

	AssetManager manager;
	PhysicsManager physManager;
	
	manager.Add("planet", planet);
	manager.Add("planet2", planet2);
	manager.Add("planet3", planet3);
	manager.Add("cst", cst);
	//manager.Add("redPlanet", surface);
	physManager.Add(cst);
	physManager.Add(planet);
	physManager.Add(planet2);
	physManager.Add(planet3);
	physManager.InitPhysVec();

	QuadTree QT(-3/2*WIDTH, 0, 3*WIDTH, HEIGHT); 
	//QT.AddGeometry(*surface);

	WorldGeometry* Geoms[30];
	std::string name = "surface";
	std::string index;
	std::string fin;
	std::stringstream num (std::stringstream::in | std::stringstream::out);
	for (int i = 0; i < 30; ++i) {
		Geoms[i] = new WorldGeometry();
		Geoms[i]->Load("../bin/planet.png");
		Geoms[i]->SetPosition(192*(i-15), HEIGHT - 190);
		Geoms[i]->SetCollidable(true);
		Geoms[i]->SetOrigin(95,95);
		QT.AddGeometry(*Geoms[i]);
		num << i;
		index = num.str();
		num.str("");
		fin = name + index;
		manager.Add(fin, Geoms[i]);
	}
	/*
	WorldGeometry* surface = new WorldGeometry();
	surface->Load("../bin/planet.png");
	surface->SetPosition(0, HEIGHT-190);
	surface->SetCollidable(true);
	surface->SetOrigin(95,95);
	*/



	planet->setVx(-180);
	planet->setVy(-40.0);
	planet2->setVx(50);
	int nFrames = 0;
	sf::Clock fClock;
	sf::Font font; //make a frame counter in a class later
	font.loadFromFile("../bin/DroidSans.tff");
	sf::Text Fps("0", font, 14);
	std::stringstream ss (std::stringstream::in | std::stringstream::out);

	std::set<WorldGeometry*> geoms;
	std::set<WorldGeometry*>::iterator geom;
	std::vector<HeavenlyBody*> bodies;
	bodies.push_back(planet);
	bodies.push_back(planet2);
	bodies.push_back(planet3);
	while (window.isOpen()) {
	
		sf::Event event;
		while (window.pollEvent(event)) {
			//player1->Interact(event); //shouldn't do this here
			if (event.type == sf::Event::Closed)
				window.close();
		}
		physManager.UpdatePhysics(physClock.restart().asSeconds());
	
		//quadTree experimentation
	
		for (int b = 0; b < 3; ++b) {	
			HeavenlyBody* plnt = bodies[b];
			for (int d = 0; d < 3; ++d) {
				if (d != b) {
					HeavenlyBody* other = bodies[d];
					//if (HaveCollided(plnt, other)) {
					if (plnt->HasCollided(other)) {

						printf("Collision Detected\n");
						//first, set up the change in radial velocity
						sf::Vector2f r = other->GetPosition() - plnt->GetPosition();
						float R = hypotf(r.x,r.y);
						sf::Vector2f sxy = other->GetPosition();
						sf::Vector2f pxy = plnt->GetPosition();
						sf::Vector2f v = (plnt->GetVelocity()*plnt->getMass() - other->GetVelocity()*other->getMass()); // dealta v (this is a diffrence of v)
						sf::Vector2f v2 = other->GetVelocity()*other->getMass(); // dealta v (this is a diffrence of v)
						sf::Vector2f v1 = plnt->GetVelocity()*plnt->getMass(); // dealta v (this is a diffrence of v)
						float damping = 0.85; //damping factor	
						sf::Vector2f frict = v;
						v1 -= r*(2.0f*(v.x*r.x+v.y*r.y)/(R*R)*damping);
						v2 += r*(2.0f*(v.x*r.x+v.y*r.y)/(R*R)*damping);
						//next, set up the change in tangential velocity

						v1 -= r*((frict.x*r.y-frict.y*r.x)/(R*R)*(1-damping)); //not real friction, 
						v2 += r*((frict.x*r.y-frict.y*r.x)/(R*R)*(1-damping)); //not real friction, 
						//but something at least, this can be fixed later

						//lastly, set up the change in angular momentum

						float omega, omega2;
						//sf::Vector2f delV = r*((frict.x*r.y-frict.y*r.x)/(R*R)*(1-damping)); //not real friction, 
						sf::Vector2f delV = frict*(1-damping); //not real friction, 
						omega = (1-damping)*(delV.x*r.x+delV.y*r.y/(R*R));//*plnt->getMass()/plnt->getI();
						omega2 = -(1-damping)*(delV.x*r.x+delV.y*r.y/(R*R));//*plnt->getMass()/plnt->getI();

						//then set the physics
						//plnt->setVx(v1.x/plnt->getMass());
						//plnt->setVy(v1.y/plnt->getMass());
						//plnt->setOmega(omega);
						plnt->setX(sxy.x-(95*other->GetRadius()+95*plnt->GetRadius())*(r.x)/R);
						plnt->setY(sxy.y-(95*other->GetRadius()+95*plnt->GetRadius())*(r.y)/R);
		
						//other->setVx(v2.x/other->getMass());
						//other->setVy(v2.y/other->getMass());
						//other->setOmega(omega2);
						//other->setX(pxy.x+(95*plnt->GetRadius()+95*other->GetRadius())*(r.x)/R);
						//other->setY(pxy.y+(95*plnt->GetRadius()+95*other->GetRadius())*(r.y)/R);

					}
				}
			}
			geoms = QT.GetContents(plnt->GetGlobalBounds());
			if (geoms.size() != 0) {
				for (geom = geoms.begin(); geom != geoms.end(); ++geom) {
					WorldGeometry* surface = *geom; //get out collider
					sf::Vector2f r = surface->GetPosition() - plnt->GetPosition(); //dealta r
					float R = hypotf(r.x,r.y);
					if (R < 95+plnt->GetRadius()*95.0) {

						//first, set up the change in radial velocity
						sf::Vector2f sxy = surface->GetPosition();
						sf::Vector2f v = plnt->GetVelocity(); // dealta v (this is a diffrence of v)
						float damping = 0.85; //damping factor	
						sf::Vector2f frict = v;
						v -= r*(2.0f*(v.x*r.x+v.y*r.y)/(R*R)*damping);
						//next, set up the change in tangential velocity

						v -= r*((frict.x*r.y-frict.y*r.x)/(R*R)*(1-damping)); //not real friction, 
						//but something at least, this can be fixed later

						//lastly, set up the change in angular momentum

						float omega;
						//sf::Vector2f delV = r*((frict.x*r.y-frict.y*r.x)/(R*R)*(1-damping)); //not real friction, 
						sf::Vector2f delV = frict*(1-damping); //not real friction, 
						omega = (1-damping)*(delV.x*r.x+delV.y*r.y/(R*R));//*plnt->getMass()/plnt->getI();

						//then set the physics
						plnt->setVx(v.x);
						plnt->setVy(v.y);
						plnt->setOmega(omega);
						plnt->setX(sxy.x-(95+95*plnt->GetRadius())*(r.x)/R);
						plnt->setY(sxy.y-(95+95*plnt->GetRadius())*(r.y)/R);
					}
				}
			}
		}
	
		//

		if (clock.getElapsedTime().asSeconds() > 1.0/FPS) {
			clock.restart();
			window.clear();
			nFrames += 1;
			manager.DrawAll(window);
			window.draw(Fps);
			window.display();
		}
		++nFrames;
		if (fClock.getElapsedTime().asSeconds() > 2.0){
			double fps = nFrames/fClock.restart().asSeconds();
			nFrames = 0;
			ss << fps;
			Fps.setString(ss.str());
			ss.str("");	
		}
	}
	return 0;
}

