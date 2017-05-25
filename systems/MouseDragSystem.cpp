#include "MouseDragSystem.h"

MouseDragSystem::MouseDragSystem(sf::RenderWindow & win, sf::View & camera)
	:win(win), camera(camera), line_started(false)
{
}

MouseDragSystem::~MouseDragSystem()
{
}

void MouseDragSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	
	if (line_started)
	{
		
		lineH->line[0].position = obj_trans->trans * click_pos;
		lineH->line[1].position = win.mapPixelToCoords(sf::Mouse::getPosition() - win.getPosition() - sf::Vector2i(10, 30), camera);
		
		sf::Vector2f impulse = lineH->line[1].position - lineH->line[0].position;
		//sf::Vector2f point = click_pos + impulse;
		//click_pos = obj_trans->trans * click_pos;
	
		sf::Transform t;
		sf::Vector2f p = t.rotate(rot->degree) * click_pos;

		//std::cout << click_pos.x << " " << click_pos.y << std::endl;
		//std::cout << crossVV(click_pos, impulse) << std::endl;
		ev.emit<ApplyForceEvent>(p, impulse, this->en);
	}

	if (!line_started && sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		for (auto entity : en.entities_with_components(pos, circ, obj_trans, linvel, angvel, rot))
		{
			//std::cout << pos->pos.x << " " << pos->pos.y << " ---- " << win.mapPixelToCoords(sf::Mouse::getPosition(), camera).x << " " << win.mapPixelToCoords(sf::Mouse::getPosition(),camera).y << std::endl;
			click_pos = win.mapPixelToCoords(sf::Mouse::getPosition() - win.getPosition() - sf::Vector2i(10,30),camera) ;
			click_pos = obj_trans->trans.getInverse() * click_pos;
			if (circ->r * circ->r > click_pos.x * click_pos.x + click_pos.y * click_pos.y)
			{
				line = en.create();
				lineH = line.assign<Line>(sf::Vector2f(0,0), sf::Vector2f(0,0), sf::Color::Magenta);
				line_started = true;
				this->en = entity;
				break;
			}
		}
	}
	else if (line_started && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		line.destroy();
		line_started = false;
	}
}
