#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <sstream>
#include "World/gameAssets.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FPS 60.0


int main(int argc, char* argv[]) {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SpaceGameThing");
	sf::Clock clock;

	PhysicalAsset planet;
	planet.Load("../bin/planet.png");
	planet.SetPosition(960, 540);
	
	while (window.isOpen()) {
	
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 1.0/FPS) {
			window.clear();
			clock.restart();
			planet.Draw(window);

			window.display();
		}
	}

	return 0;
}

