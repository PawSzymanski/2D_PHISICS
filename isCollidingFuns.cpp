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

    sf::Vector2f dPos = posH2->pos - posH1->pos;
    man.normal = vecNormalize(dPos);
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
	LinearVelocity::Handle velH1 = man.en1.component<LinearVelocity>(),
		velH2 = man.en2.component<LinearVelocity>();


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
	float vertex1Sep = vecLenght(centerCir - vertex1);
	float vertex2Sep = vecLenght(centerCir - vertex2);

	sf::Transform rotMatrix;
	rotMatrix.rotate(rotH2->degree);

	///std::cout << "separation: " << separation << std::endl;
	//system("pause");
	if (separation < EPSILON)
	{
	///	std::cout << "�RODEK" << std::endl;
		man.contactsCount = 1;
		man.normal = rotMatrix * verH2->normals[index];
		man.contacts[0] = man.normal * cirH1->r + posH1->pos;
		man.penetration = 5.0f * cirH1->r + separation;
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

        sf::Vector2f v1_c = vertex1 - centerCir;
        man.normal = rotMatrix * vecNormalize(v1_c);
		man.contactsCount = 1;
		man.contacts[0] = rotMatrix * vertex1 + posH2->pos;
		man.penetration = cirH1->r - vertex1Sep;
	}
	else if (dot2 < 0)
	{
		//std::cout << "V2" << std::endl;
		if (distanceSq(vertex2, centerCir) > (cirH1->r*cirH1->r))
			return;

        sf::Vector2f v2_c = vertex2 - centerCir;
        man.normal = rotMatrix * vecNormalize(v2_c);
		man.contactsCount = 1;
		man.contacts[0] = rotMatrix * vertex2 + posH2->pos;
		man.penetration = cirH1->r - vertex2Sep;
	}
	else
	{
		//std::cout << "BOK" << std::endl;
		man.normal = -(rotMatrix * verH2->normals[index]);
		man.contactsCount = 1;

		man.contacts[0] = man.normal * cirH1->r + posH1->pos;

		man.penetration = cirH1->r - separation;

		//std::cout << "separation: " << separation << std::endl;

		//std::cout << "normal: " << man.normal.x << " " <<man.normal.y << std::endl;
	}

}

void isCollidingPC(Manifold & man)
{
	std::swap(man.en1, man.en2);
	isCollidingCP(man);
}

sf::Vector2f GetSupport(VertexArray::Handle verH, sf::Vector2f normal)
{
	float bestDistance = -FLT_MAX;
	int bestVertex;
	for (int i = 0; i < verH->vert.getVertexCount(); ++i)
	{
		if (dot(normal, verH->vert[i].position) > bestDistance)
		{
			bestDistance = dot(normal, verH->vert[i].position);
			bestVertex = i;
		}
	}
	sf::Vector2f ver = verH->vert[bestVertex].position;
	return ver;
}

float findLeastPenetration(entityx::Entity en1, entityx::Entity en2, int &faceIndex)
{
	Position::Handle posH1 = en1.component<Position>(),
		posH2 = en2.component<Position>();
	VertexArray::Handle verH1 = en1.component<VertexArray>(),
		verH2 = en2.component<VertexArray>();
	Rotation::Handle  rotH1 = en1.component<Rotation>(),
		rotH2 = en2.component<Rotation>();
	Transform::Handle transH1 = en1.component<Transform>(),
		transH2 = en2.component<Transform>();
	sf::Transform ROTMATRIX1, ROTMATRIX2;
	ROTMATRIX1.rotate(rotH1->degree);
	ROTMATRIX2.rotate(rotH2->degree);
	//std::cout << "finding" << std::endl;
	
	float bestDistance = -FLT_MAX;
	int bestIndex;
	
	for (int i = 0; i < verH1->vert.getVertexCount(); ++i)
	{
		sf::Vector2f nUnrotated = verH1->normals[i];
		sf::Vector2f normal = ROTMATRIX1 * nUnrotated;

		normal = ROTMATRIX2.getInverse() * normal;

		sf::Vector2f furtherVerB = GetSupport(verH2, -normal);

		sf::Vector2f verA = verH1->vert[i].position;
		verA = transH1->trans *verA;
		verA -= posH2->pos;
		verA = ROTMATRIX2.getInverse() * verA;
		///
		//std::cout << "ver: " << furtherVerB.x << " " << furtherVerB.y << std::endl;
		float distanseCurr = dot(normal, furtherVerB - verA);

		if (distanseCurr > bestDistance)
		{
			bestDistance = distanseCurr;
			bestIndex = i;
		}
	}	
	faceIndex = bestIndex;
	///std::cout << "bst index: " << faceIndex << std::endl;
	return bestDistance;
}

void findIncidentFace(sf::Vector2f *ver, entityx::Entity &RefPoly,
	entityx::Entity & IncPoly, int referenceIndex)
{
	Position::Handle posHRef = RefPoly.component<Position>(),
		posHInc = IncPoly.component<Position>();
	VertexArray::Handle verHRef = RefPoly.component<VertexArray>(),
		verHInc = IncPoly.component<VertexArray>();
	Transform::Handle transHRef = RefPoly.component<Transform>(),
		transHInc = IncPoly.component<Transform>();
	Rotation::Handle  rotHRef = RefPoly.component<Rotation>(),
		rotHInc = IncPoly.component<Rotation>();
	
	sf::Transform ROTMATRIXRef, ROTMATRIXInc;
	ROTMATRIXRef.rotate(rotHRef->degree);
	ROTMATRIXInc.rotate(rotHInc->degree);
	//-
	sf::Vector2f referenceNormal = verHRef->normals[referenceIndex];
	//swiat
	referenceNormal = ROTMATRIXRef * referenceNormal;
	//B
	referenceNormal = ROTMATRIXInc.getInverse() * referenceNormal;

	int incidentFace = 0;
	float minDot = FLT_MAX;

///	std::cout << "normal: " << referenceNormal.x << " " << referenceNormal.y << std:: endl;
///	std::cout << "incydent amount: " << verHInc->vert.getVertexCount() << std::endl;

	for (int i = 0; i < verHInc->vert.getVertexCount(); ++i)
	{
		//std::cout << "inc vertex: " <<verHInc->vert[i].position.x << " " << verH22->vert[i].position.y << std::endl;
		float dotCurr = dot(referenceNormal, verHInc->normals[i]);
		if (dotCurr < minDot)
		{
			minDot = dotCurr;
			incidentFace = i;
			///std::cout << "mindot: " << minDot << std::endl  ;
		}
	}
	ver[0] = transHInc->trans * verHInc->vert[incidentFace].position;
	///std::cout << "inc index1: " << incidentFace << std::endl;
	incidentFace = (incidentFace + 1) % verHInc->vert.getVertexCount();
	ver[1] = transHInc->trans * verHInc->vert[incidentFace].position;
	///std::cout << "inc index2: " << incidentFace << std::endl;
}

int clip(sf::Vector2f normal, float c, sf::Vector2f *face)
{
	int sp = 0;
	sf::Vector2f out[2] = {
		face[0],
		face[1]
	};

	// Retrieve distances from each endpoint to the line
	// d = ax + by - c

	float d1 = dot(normal, face[0]) - c;
	float d2 = dot(normal, face[1]) - c;
	
	///std::cout << "clip data nor, fac0, face1, c" << std::endl << normal.x << " " << normal.y << std::endl <<
	///	face[0].x << " " << face[0].y << std::endl << face[1].x << face[1].y << std::endl << "c: " << c << std::endl;
	///std::cout << " d1 d2: " << d1 << " " << d2 << std::endl;
	// If negative (behind plane) clip

	if (d1 <= 0.0f) out[sp++] = face[0];
	if (d2 <= 0.0f) out[sp++] = face[1];

	// If the points are on different sides of the plane

	if (d1 * d2 < 0.0f) // less than to ignore -0.0f
	{
		// Push interesection point
		float alpha = d1 / (d1 - d2);
		out[sp] = face[0] + alpha * (face[1] - face[0]);
		++sp;
	}
	// Assign our new converted values
	face[0] = out[0];
	face[1] = out[1];
	///std::cout << "bef sp" << std::endl;
	assert(sp != 3);
	///std::cout << "sp: " << sp << std::endl;
	return sp;
}

inline bool broadphase(sf::FloatRect &a, sf::FloatRect &b)
{
   return (((b.left - a.left) < a.width && ( b.top - a.top ) < a.height) ||
           ((a.left - b.left) < b.width && ( a.top - b.top ) < b.height));
           //( (a.left > b.left  && a.left < b.left+b.width && a.top > b.top && a.top < b.top+ b.height) ||
           //(b.left > a.left  && b.left < a.left+a.width && b.top > a.top && b.top < a.top+ a.height));
}


void isCollidingPP(Manifold & man)
{
	man.contactsCount = 0;
	Position::Handle posH1 = man.en1.component<Position>(),
		posH2 = man.en2.component<Position>();
	VertexArray::Handle verH1 = man.en1.component<VertexArray>(),
		verH2 = man.en2.component<VertexArray>();
	Rotation::Handle  rotH1 = man.en1.component<Rotation>(),
		rotH2 = man.en2.component<Rotation>();

    sf::FloatRect rect1 = verH1->vert.getBounds(),
            rect2 = verH2->vert.getBounds();
    rect1.left += posH1->pos.x;
    rect1.top += posH1->pos.y;
    rect2.left += posH2->pos.x;
    rect2.top += posH2->pos.y;

    if(!broadphase(rect1, rect2))
        return;

	sf::Transform ROTMATRIX1, ROTMATRIX2;
	ROTMATRIX1.rotate(rotH1->degree);
	ROTMATRIX2.rotate(rotH2->degree);
	
	///std::cout << "." << std::endl;
		
	int faceIndexA;
	
	float penetrationA = findLeastPenetration(man.en1, man.en2, faceIndexA);
	if (penetrationA >= 0.0f)
		return;
	///std::cout << " weszo1" << std::endl;
	// Check for a separating axis with B's face planes
	int faceIndexB;
	float penetrationB = findLeastPenetration(man.en2, man.en1, faceIndexB);
	if (penetrationB >= 0.0f)
		return;
	///std::cout << " weszo2" << std::endl;
	int referenceIndex;
	bool flip;

	entityx::Entity RefPoly, IncPoly;
	if (BiasGreaterThan(penetrationA, penetrationB))
	{
		RefPoly = man.en1,
		IncPoly = man.en2;
		referenceIndex = faceIndexA;
		flip = false;
	}
	else
	{
		RefPoly = man.en2;
		IncPoly = man.en1;
		referenceIndex = faceIndexB;
		flip = true;
	}

	Position::Handle posHRef = RefPoly.component<Position>(),
		posHInc = IncPoly.component<Position>();
	VertexArray::Handle verHRef = RefPoly.component<VertexArray>(),
		verHInc = IncPoly.component<VertexArray>();
	Transform::Handle transHRef = RefPoly.component<Transform>(),
		transHInc = IncPoly.component<Transform>();
	Rotation::Handle  rotHRef = RefPoly.component<Rotation>(),
		rotHInc = IncPoly.component<Rotation>();

	sf::Transform ROTMATRIXRef, ROTMATRIXInc;
	ROTMATRIXRef.rotate(rotHRef->degree);
	ROTMATRIXInc.rotate(rotHInc->degree);

	sf::Vector2f incidentFace[2];
	findIncidentFace(incidentFace, RefPoly, IncPoly, referenceIndex);
	
	incidentFace[0] = transHRef->trans.getInverse() * incidentFace[0];
	incidentFace[1] = transHRef->trans.getInverse() * incidentFace[1];
	
	sf::Vector2f ver1 = verHRef->vert[referenceIndex].position;
	///std::cout << "ref index1: " << referenceIndex << std::endl;
	sf::Vector2f referenceNormal = verHRef->normals[referenceIndex];
	
	referenceIndex = (referenceIndex + 1) % verHRef->vert.getVertexCount();
    
	///std::cout << "ref index2: " << referenceIndex << std::endl;
	
	sf::Vector2f ver2 = verHRef->vert[referenceIndex].position;
	//ver2 = transHRef->trans * ver2;
	
	//referenceNormal = ROTMATRIXRef * referenceNormal;
	///std::cout << "ref ver1: " << ver1.x << " " << ver1.y << std::endl;
	///std::cout << "ref ver2: " << ver2.x << " " << ver2.y << std::endl;
	///std::cout << "ref amount: " << verHRef->vert.getVertexCount() << std::endl;
	//std::cout << "sideplanenormal: " << SIDEPLANENormal.x << " " << SIDEPLANENormal.y << std::endl;
	///std::cout << "begginig fef normal: " << referenceNormal.x << " " << referenceNormal.y << std::endl;
	float refC = dot(referenceNormal, ver1);
	///std::cout << " weszo3a" << " "// <<incidentFace[0].x << " " 
	///	<< incidentFace[0].y << " " << incidentFace[1].x << " " << incidentFace[1].y << " " 
	///	<< refC <<std::endl;
	
	if (clip(referenceNormal, refC , incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points
	
	if (clip(referenceNormal, refC , incidentFace) < 2)
		return; // Due to floating point error, possible to not have required points	
///	std::cout << " !!!!!!!!!!!!!weszo4" << std::endl;
	man.normal = flip ? -referenceNormal : referenceNormal;

	int clippedPoints = 0;

	float separation = dot(referenceNormal, incidentFace[0]) - refC;

	///	std::cout << "separaton1 :" << separation << std::endl;
	if (separation <= -EPSILON)
	{
		man.contacts[clippedPoints] = transHRef->trans * incidentFace[0];
		man.penetration = -separation;
		++clippedPoints;
	} 
	else
		man.penetration = 0.f;

	separation = dot(referenceNormal, incidentFace[1]) - refC;
	///std::cout << "separaton2 :" << separation << std::endl;
	if (separation <= -EPSILON)
	{
		man.contacts[clippedPoints] = transHRef->trans * incidentFace[1];
		man.penetration += -separation;
		++clippedPoints;
		man.penetration /= static_cast<float>(clippedPoints);
	}
	man.contactsCount = clippedPoints;

	man.normal = ROTMATRIXRef * man.normal;

	///std::cout << "contact points: " << (int)man.contactsCount << std::endl;

	///	std::cout << "contact0: " << man.contacts[0].x << " " << man.contacts[0].y << std::endl;

	///	std::cout << "contact1: " << man.contacts[1].x << " " << man.contacts[1].y << std::endl;

	///	std::cout << "pen: " << man.penetration << " normal: "<< man.normal.x << " "<< man.normal.y <<std::endl;
}
//!!!!!!!!!!!!!!!!!!!!!!!!   OLD CODE  !!!!!!!!!!!!!!!!!!!!!!!!

/*

float leastPenetration(VertexArray::Handle verH1, sf::Vector2f point, int &side)
{
	int verCount = verH1->vert.getVertexCount();
	float max_sep = -FLT_MAX;

	for (int i = 0; i < verCount; ++i)
	{
		float sep = dot(verH1->normals.at(i), point - verH1->vert[i].position);
		side = (sep > max_sep) ? i : side;
		max_sep = (sep > max_sep) ? sep : max_sep;
	}
	//std::cout << side << std::endl;
	return -max_sep;
}







int side=0;
//czy (2) jest w obiekcie (1)
for (int i = 0; i < verH2->vert.getVertexCount(); ++i)
{
sf::Vector2f positionOfVer = verH2->vert[i].position;
positionOfVer = transH1->trans.getInverse() *(transH2->trans * positionOfVer);
float penetration = leastPenetration(verH1, positionOfVer, side);
//std::cout << penetration << std::endl;
if (penetration > 0)
{

man.normal = ROTMATRIX1 * verH1->normals[side];
man.contacts[man.contactsCount] = transH1->trans * positionOfVer;
man.penetration = (penetration > man.penetration) ? penetration : man.penetration;
//if (man.penetration > EPSILON)
//std::cout << man.penetration << std::endl;
++man.contactsCount;
if (man.contactsCount >= 2)
return;
//std::cout << "111111" << (side + 1) % verH1->vert.getVertexCount() << man.contacts[0].x << "  " << man.contacts[0].y << std::endl;
}

}
//czy (1) jest w obiekcie (2)
for (int i = 0; i < verH1->vert.getVertexCount(); ++i)
{
sf::Vector2f positionOfVer = verH1->vert[i].position;
positionOfVer = transH2->trans.getInverse() *(transH1->trans * positionOfVer);
float penetration = leastPenetration(verH2, positionOfVer, side);
//std::cout << penetration << std::endl;
if (penetration > 0)
{

man.normal = ROTMATRIX2 * -verH2->normals[side];
man.contacts[man.contactsCount] = transH2->trans * positionOfVer;
man.penetration = (penetration > man.penetration) ? penetration : man.penetration;
//if (man.penetration > EPSILON)
//	std::cout << man.penetration << std::endl;
++man.contactsCount;
//std::cout << "2222222  " << (side + 1) % verH1->vert.getVertexCount() << " " <<man.contacts[0].x << "  "<< man.contacts[0].y <<std::endl;
//std::cout << (int)man.contactsCount << std::endl;
if (man.contactsCount >= 2)
return;
}
}*/
