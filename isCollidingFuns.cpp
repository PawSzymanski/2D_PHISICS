#include "isCollidingFuns.h"

bool isColliding(Manifold &man)
{
	Position::Handle posH1 = man.en1.component<Position>(),
		posH2 = man.en2.component<Position>();
	Circle::Handle cirH1 = man.en1.component<Circle>(),
		cirH2 = man.en2.component<Circle>();
	float sumR = cirH1->r + cirH2->r,
		dist = sqrt((posH1->pos.x - posH2->pos.x)*(posH1->pos.x - posH2->pos.x) + (posH1->pos.y - posH2->pos.y) * (posH1->pos.y - posH2->pos.y));

	if (sumR < dist)
	{	
		return false;
	}
	man.normal = vecNormalize(posH2->pos - posH1->pos);
	man.contacts[0] = posH1->pos+man.normal*cirH1->r;
	++man.contactsCount;
	man.penetration = sumR - dist;

	return true;
}
