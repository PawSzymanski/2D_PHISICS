#include "isCollidingFuns.h"

void isCollidingCC(Manifold &man)
{
	std::cout << "CC" << std::endl;
	Position::Handle posH1 = man.en1.component<Position>(),
		posH2 = man.en2.component<Position>();
	Circle::Handle cirH1 = man.en1.component<Circle>(),
		cirH2 = man.en2.component<Circle>();
	float sumR = cirH1->r + cirH2->r,
		dist = distance(posH1->pos, posH2->pos);

	if (sumR< dist)
	{
		return;
	}
	man.normal = vecNormalize(posH2->pos - posH1->pos);
	man.contacts[man.contactsCount] = posH1->pos + man.normal*cirH1->r;
	++man.contactsCount;
	man.penetration = sumR - dist;

	return;
}

void isCollidingCP(Manifold & man)
{
	std::cout << "CP" << std::endl;


}

void isCollidingPC(Manifold & man)
{
}

void isCollidingPP(Manifold & man)
{
}


