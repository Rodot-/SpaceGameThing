//some functions for generating HitBoxBase objects and other hitbox related tools
#ifndef HIT_BOX_FUNCS_H
#define HIT_BOX_FUNCS_H

#include "SFML/Graphics.hpp"
#include "../World/HitBox.h"
//NOTE/TODO: Hitboxbase needs it's own getPosition method
//it should offset the intrinsic position of the hitbox

#include "../Debug/Debug.h"

void* GenerateHitBox(const sf::Sprite& sprite) { //make a floatrect hitbox from a sprite's texture
	const sf::Image img = sprite.getTexture()->copyToImage();
	const sf::IntRect& size(sprite.getTextureRect());
	const sf::Vector2u imgSize(img.getSize());
	const sf::Uint8* pix = img.getPixelsPtr();
	pix += (size.left+size.top*imgSize.x)*4; //move the pointer to the location in the rect
	sf::Uint8 a;//the value of the alpha channel
	int top=size.height, left=size.width, bottom=0, right=0;
	for (int y = 0; y < size.height; ++y) {
		for (int x = 0; x < left; ++x) {
			a = pix[(x+y*imgSize.x)*4+3];
			if (a > 0) {
				if (y < top)
					top = y;	
				if (x < left)
					left = x;
			}
		}
		int y2 = size.height - y - 1;
		for (int x = size.width-1; x > right; --x) {
			a = pix[(x+y2*imgSize.x)*4+3];
			if (a > 0) {
				if (y2 > bottom)
					bottom = y2;
				if (x > right)
					right = x;
			}
		}
	}
	sf::FloatRect box(left, top, right-left, bottom-top);
	HitBoxBase<sf::FloatRect>* hbox = new HitBoxBase<sf::FloatRect>(box);
	return 	(void*)hbox;
}
#endif
