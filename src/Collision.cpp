#include "Math/Collision.h"
#include "Math/vmath.h"
#include "World/gameAssets.h"

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

