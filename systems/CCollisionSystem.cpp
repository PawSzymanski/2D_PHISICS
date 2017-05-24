#include "CCollisionSystem.h"



CCCollisionSystem::CCCollisionSystem()
{
}

bool CCCollisionSystem::isColliding(entityx::Entity en1, entityx::Entity en2)
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

void CCCollisionSystem::emitImpulse(entityx::Entity en1, entityx::Entity en2, entityx::EventManager & ev)
{
	
}

void CCCollisionSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Circle::Handle cirH1, cirH2;

	for (auto en1 : en.entities_with_components(cirH1))
	{
		for (auto en2 : en.entities_with_components(cirH2))
		{
			if (en1 == en2)
			{
				continue;
			}

			if (isColliding(en1,en2))
			{
				std::cout << "tak" << std::endl;
				emitImpulse(en1, en2, ev);
			}
		}
	}
}


CCCollisionSystem::~CCCollisionSystem()
{
}
