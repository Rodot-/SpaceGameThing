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
#include "World/WorldGeometry.h"
#include "Math/Collision.h"
#include "Math/QuadTree.h"
#include "Accounting/Registries.h"
#include "Debug/Debug.h"
#include "World/HitBox.h"

#define WIDTH 1920/2
#define HEIGHT 1080/2
#define FPS 120.0

int main(int argc, char* argv[]) {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SpaceGameThing");
	sf::Clock clock;
	sf::Clock physClock;

	float dt;
	float t = 0;
	PlayerShip* player1 = new PlayerShip();
	player1->Load("assets/tileSheets/walkSequence.png");
	player1->SetPosition(WIDTH/2,HEIGHT/2-400);
	player1->SetCollidable(true);
	player1->setMass(0.1);
	//HitBoxBase<sf::FloatRect> hbox1(sf::FloatRect(0,0,512,512));
	void* k;
	player1->SetHitBox(k, collision::RECT);
	player1->SetOrigin(0,0);

	AssetManager manager;
	PhysicsManager physManager;
	QuadTree QT;

	manager.Add("me", player1);
	physManager.Add(player1);
	physManager.InitPhysVec();

	printd("Creating World\n");	
	WorldGeometry* World = new WorldGeometry();
	World->SetCollidable(true);
	GameAsset* geom;
	printd("Loading World\n");	
	World->Load("");
	printd("Loading Components\n");	
	HitBoxBase<sf::FloatRect>* hbox;
	for (int i = 0; i < 10; ++i) {
		geom = new GameAsset();
		geom->Load("assets/TestTexture.png");
		hbox = new HitBoxBase<sf::FloatRect>(sf::FloatRect(0,0,512,512));
		geom->SetHitBox((void*)hbox, collision::RECT);
		World->Add("GEOM"+(i+30+'0'), *geom, sf::Vector2f(-i*512, 128*i)); 
		geom->SetCollidable(true);
	}
	World->SetHitBox((void*)hbox, collision::RECT);
	printd("Setting Up Postion and scale\n");	
	World->SetScale(0.25, 0.25);
	World->SetPosition(0.0, HEIGHT-128);
	
	printd("Adding to manager\n");	
	manager.Add("WORLD", World);
	printd("Setting Physics Manager\n");	
	physManager.SetWorld(World);
	while (window.isOpen()) {

		printd("Entering Loop from Top\n");	
		sf::Event event;
		while (window.pollEvent(event)) {
			//player1->Interact(); //shouldn't do this here
			if (event.type == sf::Event::Closed)
				window.close();
		}
		printd("Updating Physics\n");
		physManager.UpdatePhysics(physClock.restart().asSeconds());
		printd("Player Interaction\n");
		player1->Interact();
		printd("Player Has Interacted\n");
		printv(player1->GetPosition().y);
		printv(player1->GetPosition().x);
		printv(World->GetPosition().y);
		printv(World->GetPosition().x);
		//if (World->HasCollided(player1)) {
		//	printd("Collision Detected\n");
		//}
		//else {
		//	printd("No Collision Detected\n");
		//}
		//collision experimentation
		//

		printd("Ready to draw\n");
		dt = clock.restart().asSeconds();
		window.clear();
		printd("Drawing Everything\n");
		manager.DrawAll(window);
		printd("Updating Everything\n");
		manager.UpdateAll(dt);
		window.display();
		printd("Loop has ended\n");
	}

	return 0;
}

