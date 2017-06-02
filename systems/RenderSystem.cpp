#include "RenderSystem.h"



RenderSystem::RenderSystem(sf::RenderWindow& win)
	:win(win)
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	Position::Handle pos;
	Circle::Handle circ;
	Line::Handle line;
	Transform::Handle trans;
	VertexArray::Handle vArray;
	win.clear(sf::Color::Blue);

	for (auto entity : en.entities_with_components( circ, pos, line, trans ))
	{
		sf::CircleShape c_shape;
		c_shape.setFillColor(circ->color);
		c_shape.setPosition(pos->pos);
		c_shape.setRadius(circ->r);
		c_shape.setOrigin(sf::Vector2f(circ->r, circ->r));
		win.draw(c_shape);
		win.draw(line->line, trans->trans);
	}

	for (auto entity : en.entities_with_components(vArray, trans))
	{
		win.draw(vArray->vert, trans->trans);
	}

	for (auto entity : en.entities_with_components(line))
		win.draw(line->line);

	win.display();
}
