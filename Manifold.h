#pragma once
#include <entityx\entityx.h>
#include <SFML\Graphics.hpp>

//info about collisin
struct Manifold
{
	Manifold(entityx::Entity en1, entityx::Entity en2) : normal(sf::Vector2f(0, 0)), penetration(0), contactsCount(0)
	{

	}
	sf::Vector2f normal;
	float penetration;
	entityx::Entity en1, en2;
	uint8_t contactsCount;
	sf::Vector2f contacts[2];
};