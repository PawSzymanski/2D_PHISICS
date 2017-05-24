#pragma once
#include <entityx\entityx.h>
#include <SFML\Graphics.hpp>
#include <cmath>

#include "..\components.h"
#include "..\Events.h"

class CCCollisionSystem : public entityx::System<CCCollisionSystem>
{
	bool isColliding(entityx::Entity en1, entityx::Entity en2);

	void emitImpulse(entityx::Entity en1, entityx::Entity en2, entityx::EventManager & ev);

public:
	CCCollisionSystem();

	void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);

	~CCCollisionSystem();
};

