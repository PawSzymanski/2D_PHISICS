#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
}
void CollisionSystem::ResolveCollision(Manifold &m)
{
	LinearVelocity::Handle velH1 = m.en1.components<LinearVelocity>, velH2 = m.en2.components<LinearVelocity>;
	Position::Handle velH1 = m.en1.components<Position>, velH2 = m.en2.components<Position>;
	Mass::Handle velH1 = m.en1.components<Mass>, velH2 = m.en2.components<Mass>;
	//LinearVelocity::Handle velH1 = m.en1.components<LinearVelocity>, velH2 = m.en2.components<LinearVelocity>;

	sf::Vector2f relVel = velH1->vel - velH2->vel;

	velalonAlgnormal

	float force = 

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
			Manifold m(en1,en2);
			if (isColliding(m))
			{
				std::cout << "tak" << std::endl;
			}
		}
	}
}


CollisionSystem::~CollisionSystem()
{
}
