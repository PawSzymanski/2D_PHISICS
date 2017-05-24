#pragma once
#include <entityx\entityx.h>
#include <SFML\Graphics.hpp>
#include <cmath>

#include "..\isCollidingFuns.h"
#include "..\components.h"
#include "..\Events.h"

class CollisionSystem : public entityx::System<CollisionSystem>
{
public:
	CollisionSystem();

	void update(entityx::EntityManager & en, entityx::EventManager & ev, double dt);

	~CollisionSystem();
};
