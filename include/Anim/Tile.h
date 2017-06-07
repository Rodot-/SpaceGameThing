#ifndef TILE_H
#define TILE_H

#include "SFML/Graphics.hpp"
#include <string.h>
#include <stdio.h>

class Tile{

	public:

		Tile() {};
		Tile(sf::Texture* texture, const sf::IntRect Rect, const unsigned int N);

		bool isAnimated() const; //Is the sprite currently animated?
		void incrementFrame(const int n);  //increment (or decrement) frame counter by n
		void nextFrame(); //go to the next frame
		void resetAnim(); // go to the first frame
		void flipTexture(); //flip the texture left-right
		void updateAnim(); //update the animation based on the new n


		//getters
		sf::Sprite* getSprite() const;
		sf::Texture* getTexture() const;

		//setters
		void setTexture(sf::Texture* texture);
		void setAnimated(bool animState);
		void setTilePositions(unsigned int* leftTilePosition);

	private:

		unsigned int _nframes, _n; //total number of frames, current frame, top position of IntRect
		unsigned int* _leftTilePosition; //Position of the left end of the tile
		bool _isAnimated;
		sf::Sprite* _sprite; //the sprite itself
		sf::Texture* _texture; //The Tile texture
		sf::IntRect _referenceRect; //holds inforamtion about the size of the int rect we'll use.

};



#endif

