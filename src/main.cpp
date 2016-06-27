#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <sstream>

#define WIDTH 1920
#define HEIGHT 1080
#define FPS 24.0


int main(int argc, char* argv[]) {

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "SpaceGameThing");
	sf::Clock clock;

	sf::Texture planetTexture;
	if (!planetTexture.loadFromFile("../bin/planet.png")) {
		return -1;
	}
	sf::Sprite planet(planetTexture);
	planet.setOrigin(95,95);
	planet.setScale(0.5,0.5);
	planet.setPosition(960,540);

	
	while (window.isOpen()) {
	
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 1.0/FPS) {
			window.clear();

			window.draw(planet);
			planet.rotate(M_PI/12*0.01);
			window.display();
		}
	}

	return 0;
}

