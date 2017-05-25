#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
}

void CollisionSystem::ResolveCollision(Manifold &m)
{
	LinearVelocity::Handle velH1 = m.en1.component<LinearVelocity>(), velH2 = m.en2.component<LinearVelocity>();
	Position::Handle posH1 = m.en1.component<Position>(), posH2 = m.en2.component<Position>();
	Mass::Handle massH1 = m.en1.component<Mass>(), massH2 = m.en2.component<Mass>();
	AngularVelocity::Handle angvelH1 = m.en1.component<AngularVelocity>(), angvelH2 = m.en2.component<AngularVelocity>();
	MOfInertia::Handle inertH1 = m.en1.component<MOfInertia>(), inertH2 = m.en2.component<MOfInertia>();
	
	float invMassSum = massH1->invMass + massH1->invMass;
	if (equal(invMassSum, 0))
	{
		velH1->vel = sf::Vector2f(0, 0);
		velH2->vel = sf::Vector2f(0, 0);
		return;
	}

	sf::Vector2f contact1 = m.contacts[0] - posH1->pos,
		contact2 = m.contacts[0] - posH2->pos;

	sf::Vector2f contactVel = velH2->vel + crossSV(angvelH2->radians(), contact2) -
		velH1->vel - crossSV(angvelH1->radians(), contact1);

	float velAlongNormal = dot(contactVel, m.normal);
	if (velAlongNormal > 0)
		return;

	float contact1XNormal = crossVV(contact1, m.normal);
	float contact2XNormal = crossVV(contact2, m.normal);

	invMassSum += sqr(contact1XNormal) *inertH1->invI + sqr(contact2XNormal) *inertH2->invI;

	float force = -velAlongNormal / invMassSum;

	m.force = m.normal * force;
}

void CollisionSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle posH1, posH2;


	for (auto en1 : en.entities_with_components(posH1))
	{
		for (auto en2 : en.entities_with_components(posH2))
		{
			if (en1 == en2)
				continue;
			
			Manifold m(en1,en2);

			isColliding(m);

			if (!m.contactsCount)
				continue;

			ResolveCollision(m);
			
			sf::Vector2f contact1 = m.contacts[0] - posH1->pos,
				contact2 = m.contacts[0] - posH2->pos;
			
			ev.emit<ApplyForceEvent>(contact2, m.force, en2);
			ev.emit<ApplyForceEvent>(contact1, -m.force, en1);
			
			std::cout << "tak" << std::endl;
		}
	}
}


CollisionSystem::~CollisionSystem()
{
}
