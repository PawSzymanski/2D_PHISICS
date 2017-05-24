#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
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

			if (isColliding(en1, en2))
			{
				std::cout << "tak" << std::endl;
			}
		}
	}
}


CollisionSystem::~CollisionSystem()
{
}
