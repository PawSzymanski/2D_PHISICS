#pragma once

#include <entityx\entityx.h>
#include <SFML\Graphics.hpp>

struct Position : public entityx::Component<Position>
{
	Position(sf::Vector2f & pos)
		:pos(pos) {}
	sf::Vector2f pos;
};

struct Rotation : public entityx::Component<Rotation>
{
	Rotation(float degree)
		:degree(degree) {}
	float degree;
};

struct Mass : public entityx::Component<Mass>
{
	Mass(float mass)
		:mass(mass) 
		{
		if (mass != 0)
			invMass = 1.0f / mass;
		else
			invMass = 0;
		}
	float mass,
		  invMass;
};

struct LinearVelocity : public entityx::Component<LinearVelocity>
{
	LinearVelocity(sf::Vector2f & vel)
		:vel(vel) {}
	sf::Vector2f vel;
};

struct AngularVelocity : public entityx::Component<AngularVelocity>
{
	AngularVelocity(float degree)
		:degree(degree) {}
	float degree;
};

struct Circle : public entityx::Component<Circle>
{
	Circle(float r, sf::Color color)
		:r(r), color(color) {}
	sf::Color color;
	float r;
};

struct Line : public entityx::Component<Line>
{
	Line(sf::Vector2f begin, sf::Vector2f end, sf::Color col)
		:line(sf::Lines, 2)
	{
		line[0].position = begin;
		line[1].position = end;
		line[0].color = col;
		line[1].color = col;
	}

	sf::VertexArray line;
};

struct Transform : entityx::Component<Transform>
{
	sf::Transform trans;
};

struct LinearForce : entityx::Component<LinearForce> 
{
	LinearForce() : force(sf::Vector2f(0.0, 0.0)) 
	{}
	sf::Vector2f force;
};

struct AngularForce :entityx::Component<AngularForce>
{
	AngularForce() : force(0.0f)
	{}
	float force;
};