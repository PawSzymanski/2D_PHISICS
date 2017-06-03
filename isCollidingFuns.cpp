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
	rotMatrix.rotate(rotH2->degree);

	//std::cout << "d: " << rotH2->degree<< std::endl;

	if (separation < EPSILON)
	{
		std::cout << "ŒRODEK" << std::endl;
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
		std::cout << "V1" << std::endl;
		if (distanceSq(vertex1, centerCir) > (cirH1->r*cirH1->r) )
			return;
		man.normal = rotMatrix * vecNormalize(vertex1 - centerCir);
		man.contactsCount = 1;
		man.contacts[0] = rotMatrix * vertex1 + posH2->pos;
		man.penetration = cirH1->r - separation;
	}
	else if (dot2 < 0)
	{
		std::cout << "V2" << std::endl;
		if (distanceSq(vertex2, centerCir) > (cirH1->r*cirH1->r))
			return;
		man.normal = rotMatrix * vecNormalize(vertex2 - centerCir);
		man.contactsCount = 1;
		man.contacts[0] = rotMatrix * vertex2 + posH2->pos;
		man.penetration = cirH1->r - separation;
	}
	else
	{
		std::cout << "BOK" << std::endl;
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



float leastPenetration(VertexArray::Handle verH1, sf::Vector2f point, int &side)
{
	int verCount = verH1->vert.getVertexCount();
	float max_sep = -FLT_MAX;
	for (int i = 0; i < verCount; ++i)
	{
		float sep = dot(verH1->normals.at(i), point - verH1->vert[i].position);
		max_sep = (sep > max_sep) ? sep : max_sep;
		side = (sep > max_sep) ? i : side;
	}

	return -max_sep;
}




void isCollidingPP(Manifold & man)
{

	Position::Handle posH1 = man.en1.component<Position>(),
		posH2 = man.en2.component<Position>();
	VertexArray::Handle verH1 = man.en1.component<VertexArray>(),
		verH2 = man.en2.component<VertexArray>();
	Transform::Handle transH1 = man.en1.component<Transform>(),
		transH2 = man.en2.component<Transform>();
	Rotation::Handle  rotH1 = man.en1.component<Rotation>(),
		rotH2 = man.en2.component<Rotation>();
	sf::Transform ROTMATRIX1, ROTMATRIX2;
	ROTMATRIX1.rotate(rotH1->degree);
	ROTMATRIX2.rotate(rotH2->degree);
	int side=0;
  //cz (2) jest w obiekcie (1)
	for (int i = 0; i < verH2->vert.getVertexCount(); ++i)
	{
		sf::Vector2f positionOfVer = verH2->vert[i].position;
		positionOfVer = transH1->trans.getInverse() *(transH2->trans * positionOfVer);	
		float penetration = leastPenetration(verH1, positionOfVer, side);		
		//std::cout << penetration << std::endl;
		if (penetration > 0)
		{
			man.contactsCount = 1;
			man.normal = ROTMATRIX1 * verH1->normals[side];
			man.contacts[0] = transH1->trans * positionOfVer;
			man.penetration = penetration;
			std::cout << "111111" << std::endl;
			return;
		}
	}
	//cz (2) jest w obiekcie (1)
	for (int i = 0; i < verH1->vert.getVertexCount(); ++i)
	{
		sf::Vector2f positionOfVer = verH1->vert[i].position;
		positionOfVer = transH2->trans.getInverse() *(transH1->trans * positionOfVer);
		float penetration = leastPenetration(verH2, positionOfVer, side);
		//std::cout << penetration << std::endl;
		if (penetration > 0)
		{
			man.contactsCount = 1;
			man.normal = ROTMATRIX2 * verH2->normals[side];
			man.contacts[0] = transH2->trans * positionOfVer;
			man.penetration = penetration;
			std::cout << "2222222" << std::endl;
			return;
		}
	}
	
}


