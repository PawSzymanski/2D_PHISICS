#pragma once

#include <iostream>
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

#include "systems/CollisionSystem.h"
#include "systems/ForcesSystem.h"
#include "systems/MouseDragSystem.h"
#include "systems/MovementSystem.h"
#include "systems/RenderSystem.h"
#include "systems/jointsystem.h"
#include "Container.h"
#include "components.h"


class MainLoop
{
	sf::RenderWindow window;
	sf::View camera;
	entityx::EntityX ex;
    Container vertCont;
	sf::Vector2f mouse_posf;
	sf::Vector2f gravity;
public:
	
	MainLoop();
	~MainLoop();

	void setSystems();
	void update(float);
	void loop();
	void render();

private:
    entityx::Entity createCircle(sf::Vector2f pos, sf::Vector2f vel, float mass, sf::Color col, float r);

    entityx::Entity createPolygon(sf::Vector2f pos, sf::Vector2f vel, float rotation, float mass, int polyIndex);

    void createJoint(entityx::Entity en1, entityx::Entity en2, sf::Vector2f pos1, sf::Vector2f pos2, float lenght);
};

