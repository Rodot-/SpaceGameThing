#include "World/CollisionHandling.h"



void* apply_transform(HitBox& hbox, sf::Transform& transform) {

	void* result = hbox->GetGeometry();
	switch (hbox.GetFlag()) {

		case (RECT):

			sf::FloatRect* geometry = new sf:FloatRect;
			*geometry = *static_cast<sf::FloatRect*>(hbox.GetGeometry())
			*geometry = transform.transformRect(*geometry);
			result = static_cast<void*>geometry;
			break;
	}
	return result;
}


bool geometry_has_collided(void* A, hb_flag A_flag, void* B, hb_flag B_flag) {

	typedef std::pair<sf::Vector2f, float> circle;
	typedef sf::FloatRect rectangle;
	typedef sf::ConvexShape convex;

	unsigned int flag = static_cast<unsigned int>(A_flag | B_flag);
	switch (flag) {

		case 1: //radial radial
			circle *c1, *c2;
			c1 = static_cast<circle*>(A);
			c2 = static_cast<circle*>(B);
				
			break;
	
		case 2: //rect rect
			rectangle *r1, *r2;
			r1 = static_cast<rectangle*>(A);
			r2 = static_cast<rectangle*>(B);

			break;

		case 3: //radial rect
			circle* c;
			rectangle* r;
			switch (A_flag) {
				case RECT:
					r = static_cast<rectangle*>(A);
					c = static_cast<circle*>(B);
					break;
				case RADIAL:
					r = static_cast<rectangle*>(B);
					c = static_cast<circle*>(A);
					break;
			}

			break;

		case 4: //convex convex
			convex *c1, *c2;
			c1 = static_cast<convex*>(A);
			c2 = static_cast<convex*>(B);

			break;


		case 5: //radial convex

			break;
				
	
		case 6: //rect convex

			break;

		case 7; //radial convex

			break;

	}

}

bool has_collided(GameAsset* A, GameAsset* B) {


	HitBox A_hb, B_hb;
	A_hb = A->GetHitBox();
	B_hb = B->GetHitBox();

	void *A_geom, *B_geom;
	A_geom = apply_transform(A_hb, A->GetTransform());
	B_geom = apply_transform(B_hb, B->GetTransform());

		

}
