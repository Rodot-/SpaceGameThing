
#include "Anim/Tile.h"


Tile::Tile(sf::Texture* texture, const sf::IntRect Rect, const unsigned int N) {

	_texture = texture;
    _referenceRect = Rect;
	_nframes = N;
	_n = 0;
	_sprite = new sf::Sprite;
	_sprite->setTexture(*_texture);
	_sprite->setTextureRect(sf::IntRect(Rect));
	_isAnimated = false;	
	_leftTilePosition = (unsigned int*)malloc(sizeof(unsigned int)*_nframes);

}


bool Tile::isAnimated(void) const { return _isAnimated; }

sf::Sprite* Tile::getSprite(void) const { return _sprite; }
sf::Texture* Tile::getTexture(void) const { return _texture; }


void Tile::setTexture(sf::Texture* texture) { _texture = texture; }

void Tile::setAnimated(bool animState) { _isAnimated = animState; }

void Tile::setTilePositions(unsigned int* leftTilePosition) { 
	memcpy(_leftTilePosition, leftTilePosition, sizeof(unsigned int)*_nframes);
}


void Tile::incrementFrame(const int n) { _n += n; _n %= _nframes; }
void Tile::nextFrame(void) { _n++; _n %= _nframes; }
void Tile::resetAnim(void) { _n = 0; }

void Tile::updateAnim(void) {	
	_sprite->setTextureRect(sf::IntRect(_leftTilePosition[_n], _referenceRect.top, _referenceRect.width, _referenceRect.height)); 
}



