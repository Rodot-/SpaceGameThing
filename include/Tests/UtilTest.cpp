//test functions in the util folder
#include <stdio.h>
#include <string.h>
#include "../Utils/Ordering.h"
#include "../Utils/HitBoxFuncs.h"
#include "../Debug/Debug.h"
#include "SFML/Graphics.hpp"
#include "../World/HitBox.h"

void printArr(int* start, int size) {

	for (int i = 0; i < size; ++i) {
		printf("%i ", *(start + i));
	}
	printf("\n");
};


int main(void) {

	sf::RenderWindow window(sf::VideoMode(1920,1080), "TEST");
	int word[8] = {7,3,6,2,6,9,1,6};
	printArr(word, 8);
	SORT(word, word + 8);
	printArr(word, 8);

	char numbers[6] = "54321";
	SORT(numbers, numbers + 5);
	printf("%s\n", numbers);

	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile("../../bin/tileSheets/walkSequence.png");
	//texture.loadFromFile("../../bin/planet.png");

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(6144-512,512,512,512));
	HitBoxBase<sf::FloatRect> hbox = *(HitBoxBase<sf::FloatRect>*)GenerateHitBox(sprite);
	printv(hbox._hbox.top);	
	printv(hbox._hbox.left);	
	printv(hbox._hbox.width);	
	printv(hbox._hbox.height);	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
	

	return 0;
}

