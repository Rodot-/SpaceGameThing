#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <sstream>
#include "Anim/Tile.h"

#define WIDTH 1920
#define HEIGHT 1080
#define FPS 60.0


void animate(sf::Sprite* sprite) {

	const sf::Texture* texture = sprite->getTexture();
	const sf::IntRect intrect = sprite->getTextureRect();
	sf::Vector2u size = texture->getSize();
	unsigned int new_left = (intrect.left+128) % size.x;
	sprite->setTextureRect(sf::IntRect(new_left, 0, 128, 128));
}
	

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


	sf::Texture walkTexture;
	if (!walkTexture.loadFromFile("../bin/walkSequenceSmall.png")) {
		return -1;
	}
	sf::Sprite man(walkTexture, sf::IntRect(0,0,128,128));
	man.setOrigin(64,0);
	man.setPosition(960,540);
	man.setScale(2,2);
	
	while (window.isOpen()) {
	
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (clock.getElapsedTime().asSeconds() > 1.0/FPS) {
			window.clear();
			clock.restart();
			window.draw(man);
			window.draw(planet);
			planet.rotate(M_PI/4*1.0/FPS);
			animate(&man);
			planet.move(std::cos(clock.getElapsedTime().asSeconds())*0.5, 0.5*std::sin(clock.getElapsedTime().asSeconds()));
			window.display();
		}
	}

	return 0;
}

