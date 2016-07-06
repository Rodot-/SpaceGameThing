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

	float dt;

	AssetManager manager;

	PhysicalAsset* planet = new PhysicalAsset();
	planet->Load("../bin/planet.png");
	planet->SetPosition(960, 540);

	PhysicalAsset* planet2 = new PhysicalAsset();
	planet2->Load("../bin/planet.png");
	planet2->SetPosition(500, 640);

	HeavenlyBody* planet3 = new HeavenlyBody(0.25, 100.5, QUIET);
	planet3->Load("../bin/planet.png");
	planet3->SetPosition(1200, 440);

	planet3->setVx(5.1);
	planet3->setVy(10.1);

	manager.Add("Pluto", planet3);
	manager.Add("Mercury", planet2);
	manager.Add("Mars", planet);

	while (window.isOpen()) {
	
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 1.0/FPS) {
			window.clear();
			dt = clock.restart().asSeconds();
		
			manager.DrawAll(window);
	
			planet3->Update(dt);

			window.display();
		}
	}

	return 0;
}

