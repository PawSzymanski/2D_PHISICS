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

	float restitution = 0.5f;

	if (equal(massH1->invMass + massH2->invMass, 0))
	{
		velH1->vel = sf::Vector2f(0, 0);
		velH2->vel = sf::Vector2f(0, 0);
		return;
	}

	// for(int i=0; i<m.contantCount ; ++i)
	//{

	sf::Vector2f contact1 = m.contacts[0] - posH1->pos,
		contact2 = m.contacts[0] - posH2->pos;

	sf::Vector2f relativeVel = velH2->vel + crossSV(angvelH2->radians(), contact2) -
		velH1->vel - crossSV(angvelH1->radians(), contact1);

	float contactVel = dot(relativeVel, m.normal);
	
	//std::cout << vecLenght(relativeVel) << " " << vecLenght(m.normal) << std:: endl;
	if (contactVel > 0)
		return;

	float contact1XNormal = crossVV(contact1, m.normal);
	float contact2XNormal = crossVV(contact2, m.normal);
	float invMassSum = massH1->invMass + massH2->invMass + sqr(contact1XNormal) *inertH1->invI + sqr(contact2XNormal) *inertH2->invI;

	float force = -(1.0f + restitution) * contactVel;
	force /= invMassSum;
	//force/= m.contactsCount;

	m.force =  m.normal * force;
	//std::cout << vecLenght(m.force) * invMassSum << std::endl;
	
	//std::cout << contactVel.x << " " << contactVel.y << std::endl;
	//friction 
	sf::Vector2f t =( relativeVel - ( m.normal * dot(relativeVel, m.normal)));
	t= vecNormalize(t);
	//std::cout << "friction: " << t.x <<" "<<t.y<< std::endl;

	float jt = -dot(relativeVel, t);

	jt /= invMassSum;
	
	if (equal(jt, 0.0f))
		return;
	sf::Vector2f frictionImpulse;

	if(abs_f(jt) < force * 0.7)
		frictionImpulse = t *jt;
	else
		frictionImpulse = t * -force * 0.5f;

	m.force += frictionImpulse;

	//}
}

void CollisionSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle posH1, posH2;
	Type::Handle typeH1, typeH2;
	LinearForce::Handle linFH1, linFH2;


	entityx::Entity * ens = new entityx::Entity[en.size()];
	int entitiesCount = 0;

	for (auto en : en.entities_with_components(posH1, typeH1, linFH1))
	{
		ens[entitiesCount] = en;
		++entitiesCount;
	}

	for(int i=0; i<entitiesCount; ++i)
	{
		ev.emit<ApplyForceEvent>(sf::Vector2f(0, 0), sf::Vector2f(0, 0.098), ens[i]); //GRAWITEJSZYN

		for (int j=i+1; j<entitiesCount; ++j)
		{			
			Manifold m(ens[i],ens[j]);

			typeH1 = ens[i].component<Type>();
			typeH2 = ens[j].component<Type>();
			posH1 = ens[i].component<Position>();
			posH2 = ens[j].component<Position>();

			dispatch[typeH1->type][typeH2->type](m);

			if (!m.contactsCount)
				continue;

			ResolveCollision(m);
			
			sf::Vector2f contact1 = m.contacts[0] - posH1->pos,
				contact2 = m.contacts[0] - posH2->pos;
			
			ev.emit<ApplyForceEvent>(contact2, m.force, ens[j]);
			ev.emit<ApplyForceEvent>(contact1, -m.force, ens[i]);
			
			//std::cout << "tak: " <<m.penetration<< std::endl;
		}
	}
}


CollisionSystem::~CollisionSystem()
{
}
