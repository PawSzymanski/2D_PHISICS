#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
	dispatch[Type::CIRCLE][Type::CIRCLE] = isCollidingCC;
	dispatch[Type::CIRCLE][Type::POLYGON] = isCollidingCP;
	dispatch[Type::POLYGON][Type::CIRCLE] = isCollidingPC;
	dispatch[Type::POLYGON][Type::POLYGON] = isCollidingPP;
}

void CollisionSystem::ResolveCollision(Manifold &m)
{
	LinearVelocity::Handle velH1 = m.en1.component<LinearVelocity>(), velH2 = m.en2.component<LinearVelocity>();
	Position::Handle posH1 = m.en1.component<Position>(), posH2 = m.en2.component<Position>();
	Mass::Handle massH1 = m.en1.component<Mass>(), massH2 = m.en2.component<Mass>();
	AngularVelocity::Handle angvelH1 = m.en1.component<AngularVelocity>(), angvelH2 = m.en2.component<AngularVelocity>();
	MOfInertia::Handle inertH1 = m.en1.component<MOfInertia>(), inertH2 = m.en2.component<MOfInertia>();
	Friction::Handle frH1 = m.en1.component<Friction>(), frH2 = m.en2.component<Friction>();

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
	std::cout << contactVel.x << " " << contactVel.y << std::endl;
	//friction 
	contactVel -= m.normal * dot(contactVel, m.normal);

	//from contact
	contactVel *= -(frH1->fr + frH2->fr) / 2;

	contactVel /= invMassSum;

	m.force += contactVel;
}

void CollisionSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle posH1, posH2;
	Type::Handle typeH1, typeH2;

	for (auto en1 : en.entities_with_components(posH1, typeH1))
	{
		for (auto en2 : en.entities_with_components(posH2, typeH2))
		{
			if (en1 == en2)
				continue;
			
			Manifold m(en1,en2);

			dispatch[typeH1->type][typeH2->type](m);

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
