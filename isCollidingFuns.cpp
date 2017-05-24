#include "isCollidingFuns.h"

bool isColliding(entityx::Entity en1, entityx::Entity en2)
{
	Position::Handle posH1 = en1.component<Position>(),
		posH2 = en2.component<Position>();
	Circle::Handle cirH1 = en1.component<Circle>(),
		cirH2 = en2.component<Circle>();
	float sumR = cirH1->r + cirH2->r,
		space = sqrt((posH1->pos.x - posH2->pos.x)*(posH1->pos.x - posH2->pos.x) + (posH1->pos.y - posH2->pos.y) * (posH1->pos.y - posH2->pos.y));
	if (sumR > space)
	{
		return true;
	}
	return false;
}
