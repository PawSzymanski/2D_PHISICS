#pragma once
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include "../components.h"

class RenderSystem : public entityx::System<RenderSystem>
{
	sf::RenderWindow &win;

public:
	RenderSystem(sf::RenderWindow& win);
	~RenderSystem();

	void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);
};

