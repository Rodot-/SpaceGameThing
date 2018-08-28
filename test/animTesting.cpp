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
#include "World/PlayerShip.h"
#include "World/TheHeavens.h"
#include "World/HitBox.h"
#include "Math/Collision.h"
#include "Accounting/Registries.h"
//#include "World/Ship.h"

#define WIDTH 1920/2
#define HEIGHT 1080/2
#define FPS 60.0
#define DEBUG_MSG

int main(int argc, char* argv[]) {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SpaceGameThing");
	sf::Clock clock;
	sf::Clock physClock;

	float dt;

	PlayerShip* player1 = new PlayerShip();
	player1->Load("assets/tileSheets/walkSequence.png");
	player1->SetPosition(WIDTH/2,HEIGHT/2);
	player1->SetCollidable(true);
	player1->setMass(0.1);
	//player1->setPhysical(false);

	HeavenlyBody* planet = new HeavenlyBody(1.0, 100000, QUIET);
	planet->Load("assets/planet.png");
	planet->SetPosition(95, HEIGHT-95);
	planet->SetCollidable(true);
	planet->SetOrigin(95,95);

	//Ship* MyShip = GetShip();

	AssetManager manager;
	PhysicsManager physManager;

	manager.Add("me", player1);
	//manager.Add("ship", MyShip);
	manager.Add("planet", planet);
	physManager.Add(player1);
	physManager.Add(planet);
	physManager.InitPhysVec();
	//need to allocate a world otherwise we get a seg fault

	while (window.isOpen()) {
	
		sf::Event event;
		while (window.pollEvent(event)) {
			//player1->Interact(event); //shouldn't do this here
			if (event.type == sf::Event::Closed)
				window.close();
		}
	
		//collision experimentation
		if (player1->GetGlobalBounds().intersects(planet->GetGlobalBounds())) {
			player1->setX(planet->GetGlobalBounds().width);
			printf("%f\n", player1->GetGlobalBounds().width);
			printf("%f\n", planet->GetGlobalBounds().width);
		}
		if (player1->getPhysVec()[1] > HEIGHT/2) { 
			player1->setY(HEIGHT/2);
			player1->setVy(0);
		}
		//

		//if (clock.getElapsedTime().asSeconds() > 1.0/FPS) {
			player1->Interact();
			float dt = physClock.restart().asSeconds();
			physManager.UpdatePhysics(dt);
			clock.restart();
			window.clear();
			//printf("...");

			manager.UpdateAll(dt);	
			manager.DrawAll(window);
			window.display();
		//}
	}

	return 0;
}

