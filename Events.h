#pragma once

#include <SFML/Graphics.hpp>
#include <entityx/entityx.h>

struct ApplyForceEvent
{
	ApplyForceEvent(sf::Vector2f point, sf::Vector2f force, entityx::Entity en)
		:point(point), force(force), en(en) {}
	sf::Vector2f point, force;
	entityx::Entity en;
};
