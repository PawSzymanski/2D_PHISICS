#include "AddForceToPLayer.h"

AddForceToPlayer::AddForceToPlayer()
{
}

void AddForceToPlayer::update(entityx::EntityManager & en, entityx::EventManager & ev, double dt)
{
	VertexArray::Handle verH;
	Line::Handle lineH;
	Rotation::Handle rotH;
	Position::Handle posH, posPlayerH;
	ForcePoint::Handle pointH;
	KeyAssigned::Handle keyH;

	for (auto en1 : en.entities_with_components(verH))
	{
		for (auto en2 : en.entities_with_components(posH, lineH,pointH,keyH))
		{
			//posPlayerH = en1.component<Position>;
			rotH = en1.component<Rotation>();
			posH = en1.component<Position>();
			
			pointH = en2.component<ForcePoint>();
			keyH = en2.component<KeyAssigned>();
			lineH = en2.component<Line>();

			sf::Transform rotMatrix;
			rotMatrix.rotate(rotH->degree);

			pointH->point = rotMatrix * pointH->point;
			pointH->force = rotMatrix * pointH->force;

			sf::Vector2f vec00 = pointH->point;
			vec00 += posH->pos;

			lineH->line[0].position = vec00;
			lineH->line[1].position = vec00 - pointH->force;

			if (sf::Keyboard::isKeyPressed(keyH->key))
			{
				ev.emit<ApplyForceEvent>(pointH->point, pointH->force, en1);
			}
			pointH->point = rotMatrix.getInverse() * pointH->point;
			pointH->force = rotMatrix.getInverse() * pointH->force;
		}
	}
}

AddForceToPlayer::~AddForceToPlayer()
{
}
