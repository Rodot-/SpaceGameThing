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

#define WIDTH 1920
#define HEIGHT 1080
#define FPS 60.0


int main(int argc, char* argv[]) {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SpaceGameThing");
	sf::Clock clock;
	sf::Clock physClock;

	float dt;

	AssetManager manager;
	PhysicsManager physManager;

	HeavenlyBody* planet = new HeavenlyBody(1.0, 1.0, QUIET);
	planet->Load("../bin/planet.png");
	planet->SetPosition(960, 540);
	planet->SetOrigin(planet->GetLocalBounds().width/2, planet->GetLocalBounds().height/2);

	HeavenlyBody* planet2 = new HeavenlyBody(0.1, 0.1, QUIET);
	planet2->Load("../bin/planet.png");
	planet2->SetPosition(500, 640);
	planet2->SetOrigin(planet2->GetLocalBounds().width/2, planet2->GetLocalBounds().height/2);

	HeavenlyBody* planet3 = new HeavenlyBody(0.25, 100.5, QUIET);
	planet3->Load("../bin/planet.png");
	planet3->SetPosition(1200, 440);
	planet3->SetOrigin(planet3->GetLocalBounds().width/2, planet3->GetLocalBounds().height/2);

	HeavenlyBody* moon = new HeavenlyBody(0.075, 0.5, QUIET);
	moon->Load("../bin/planet.png");
	moon->SetOrigin(moon->GetLocalBounds().width/2, moon->GetLocalBounds().height/2);
	
	planet3->setMass(104);
	planet2->setMass(10);
	planet->setMass(525);

	manager.Add("Phobos", moon);
	manager.Add("Pluto", planet3);
	manager.Add("Mercury", planet2);
	manager.Add("Mars", planet);

	physManager.Add(moon);
	physManager.Add(planet3);
	physManager.Add(planet);
	physManager.Add(planet2);
	physManager.InitPhysVec();

	moon->SetColor(sf::Color(255,255,255,255));

	planet2->BindToHost(*planet, 500);
	planet2->SetColor(sf::Color(255, 0, 255, 255));

	planet3->BindToHost(*planet, 200);

	moon->BindToHost(*planet2, 20);

	planet->setOmega(M_PI/8);
	planet2->setOmega(M_PI/4);
	planet3->setOmega(M_PI/2);
	moon->setOmega(M_PI/12);

	planet3->SetColor(sf::Color(0, 255, 255, 255));

	planet->setVx(0.0);
	planet->setVy(-(planet2->GetVelocity().y*planet2->getMass()+planet3->GetVelocity().y*planet3->getMass())/planet->getMass());

	while (window.isOpen()) {
	
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 1.0/FPS) {
			clock.restart();
			physManager.UpdatePhysics(physClock.restart().asSeconds());
			window.clear();
		
			manager.DrawAll(window);
	
			window.display();
		}
	}

	return 0;
}

