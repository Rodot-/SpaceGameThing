
#include "Math/Collision.h"

inline bool RadialRadial(const sf::Vector2f& p1, float r1, const sf::Vector2f& p2, float r2) {

	return (hypotf(p1.x-p2.x, p1.y-p2.y) < (r1 + r2));
}

inline bool RectRect(const sf::FloatRect& R1, const sf::FloatRect& R2) {
	
	return R1.intersects(R2);
}

inline bool RadialRect(const sf::Vector2f& p1, float r1, const sf::FloatRect& R1) {

	sf::Vector2f A;
	sf::Vector2f B;
	sf::Vector2f C;
	sf::Vector2f D;
	A.x = R1.left; A.y = R1.top;
	B.x = A.x + R1.width; B.y = A.y;
	C.x = B.x; C.y = B.y + R1.height;
	D.x = A.x; D.y = C.y;
	return (RadialLine(p1,r1,A,B) || RadialLine(p1,r1,B,C) || RadialLine(p1,r1,C,D) || RadialLine(p1,r1,D,A));

}

inline bool RadialLine(const sf::Vector2f& p1, float r1, const sf::Vector2f& A, const sf::Vector2f& B) {

	return (abs((B.y-A.y)*p1.x-(B.x-A.x)*p1.y+B.x*A.y-B.y*A.x)/(sqrt(pow((B.y-A.y),2)+pow((B.x-A.x),2))) < r1);
}

bool HaveCollided(GameAsset* A, GameAsset* B) {

	if (!A->IsCollidable() || !B->IsCollidable())
		return false;
	if (!A->GetGlobalBounds().intersects(B->GetGlobalBounds()))
		return false;
	collision::type act = A->GetCollision();
	collision::type bct = B->GetCollision();

	if (act == bct) {
		switch (act) {
			case collision::RADIAL:
				return RadialRadial(A->GetPosition(), A->GetRadius(), B->GetPosition(), B->GetRadius());
				break;
			
			case collision::RECT:
				return RectRect(A->GetGlobalBounds(), B->GetGlobalBounds());
				break;
		}
	}
	else {
		if (act == collision::RADIAL) {
			if (bct == collision::RECT) {
				return RadialRect(A->GetPosition(), A->GetRadius(), B->GetGlobalBounds());	
			}
		}
		else if (act == collision::RADIAL) {
			if (bct == collision::RECT) {
				return RadialRect(B->GetPosition(), B->GetRadius(), A->GetGlobalBounds());
			}
		}
	}
}

