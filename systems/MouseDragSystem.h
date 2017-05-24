#pragma once
#include <entityx\entityx.h>
#include <SFML\Graphics.hpp>
#include "..\components.h"
#include "..\Events.h"


class MouseDragSystem : public entityx::System<MouseDragSystem>
{
	entityx::Entity line, en;
	LinearVelocity::Handle linvel;
	AngularVelocity::Handle angvel;
	Position::Handle pos;
	Rotation::Handle rot;
	Circle::Handle circ;
	Line::Handle lineH;
	Transform::Handle obj_trans;
	sf::Vector2f click_pos;
	bool line_started;
	sf::RenderWindow &win;
	sf::View & camera;

public:
	MouseDragSystem(sf::RenderWindow & win, sf::View & camera);
	~MouseDragSystem();

	void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);
};

