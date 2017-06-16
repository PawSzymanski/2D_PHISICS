#pragma once
#include <vector>
#include <cmath>
#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>

class Container
{
public:
	Container();

	std::vector<sf::VertexArray> vertexArrays;
	std::vector<std::vector<sf::Vector2f>> normals;

	void addPoly(sf::VertexArray & v, int size);

	~Container();
};

