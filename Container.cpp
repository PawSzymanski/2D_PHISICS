#include "Container.h"



Container::Container()
{
}

void Container::addPoly(sf::VertexArray & v, int size)
{
	std::vector <sf::Vector2f> n;
	vertexArrays.push_back(v);
	for (int i = 0; i <size; ++i)
	{										
		sf::Vector2f a = v[i].position, b = v[(i + 1) % size].position,
			side = a - b;
		sf::Transform trans;
		trans.rotate(90);
		side = trans * side;
		float lenght = sqrt(side.x*side.x + side.y*side.y);
		side /= lenght;
		n.push_back(side);
	}

	normals.push_back(n);

	std::cout << " size :"  <<normals[0].size() << std::endl;
}

Container::~Container()
{
}
