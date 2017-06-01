#include "isCollidingFuns.h"

void isCollidingCC(Manifold &man)
{
	//std::cout << "CC" << std::endl;
	Position::Handle posH1 = man.en1.component<Position>(),
		posH2 = man.en2.component<Position>();
	Circle::Handle cirH1 = man.en1.component<Circle>(),
		cirH2 = man.en2.component<Circle>();
	float sumR = cirH1->r + cirH2->r,
		dist = distance(posH1->pos, posH2->pos);

	if (sumR< dist)
	{
		return;
	}
	man.normal = vecNormalize(posH2->pos - posH1->pos);
	man.contacts[man.contactsCount] = posH1->pos + man.normal*cirH1->r;
	++man.contactsCount;
	man.penetration = sumR - dist;

	return;
}

void isCollidingCP(Manifold & man)
{
	//std::cout << "." << std::endl;
	//std::cout << "CP" << std::endl;
	Position::Handle posH1 = man.en1.component<Position>(),
		 posH2 = man.en2.component<Position>();
	Circle::Handle cirH1 = man.en1.component<Circle>();
	VertexArray::Handle verH2 = man.en2.component<VertexArray>();
	Transform::Handle transH2 = man.en2.component<Transform>();
	Rotation::Handle rotH2 = man.en2.component<Rotation>();

	sf::Vector2f centerCir =  (transH2->trans.getInverse() * (posH1->pos)) ;
	int index = 0;
	float separation = -FLT_MAX;
	int vertSize = verH2->vert.getVertexCount();
	

	for (int a = 0; a < vertSize; ++a)
	{
		//std::cout << verH2->vert[a].position.x << " "<< verH2->vert[a].position.y<<std::endl;
		float sepHelp = dot(verH2->normals.at(a), centerCir - verH2->vert[a].position);
		if (sepHelp > cirH1->r)
			return;
		
		if (sepHelp > separation)
		{
			separation = sepHelp;
			index = a;
		}	
	}
	sf::Vector2f vertex1 = verH2->vert[index].position,
		vertex2 = verH2->vert[(index+1) % vertSize].position;

	sf::Transform rotMatrix;
	rotMatrix.rotate(rotH2->degree / 57.29577);

	if (separation < EPSILON)
	{
	//	std::cout << "ŒRODEK" << std::endl;
		man.contactsCount = 1;
		man.normal = rotMatrix * verH2->normals[index];
		man.contacts[0] = man.normal * cirH1->r + posH1->pos;
		man.penetration = cirH1->r;
		return;
	}

	float dot1 = dot(centerCir - vertex1, vertex2 - vertex1);
	float dot2 = dot(centerCir - vertex2, vertex1 - vertex2);
	//std::cout << "dot1:  "<< centerCir.x << " " << centerCir.y << std::endl;
	if (dot1 < 0)
	{
		//std::cout << "V1" << std::endl;
		if (distanceSq(vertex1, centerCir) > (cirH1->r*cirH1->r) )
			return;
		man.normal = rotMatrix * vecNormalize(vertex1 - centerCir);
		man.contactsCount = 1;
		man.contacts[0] = rotMatrix * vertex1 + posH2->pos;
		man.penetration = cirH1->r - separation;
	}
	else if (dot2 < 0)
	{
		//std::cout << "V2" << std::endl;
		if (distanceSq(vertex2, centerCir) > (cirH1->r*cirH1->r))
			return;
		man.normal = rotMatrix * vecNormalize(vertex2 - centerCir);
		man.contactsCount = 1;
		man.contacts[0] = rotMatrix * vertex2 + posH2->pos;
		man.penetration = cirH1->r - separation;
	}
	else
	{
		//std::cout << "BOK" << std::endl;
		man.normal = -(rotMatrix * verH2->normals[index]);
		man.contactsCount = 1;
		man.contacts[0] = -(man.normal * cirH1->r) + posH1->pos;
		man.penetration = cirH1->r - separation;

		//std::cout << "normal: " << man.normal.x << " " <<man.normal.y << std::endl;
	}

}

void isCollidingPC(Manifold & man)
{

}

void isCollidingPP(Manifold & man)
{
}


