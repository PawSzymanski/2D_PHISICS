#include <entityx/entityx.h>
#include <SFML/Graphics.hpp>
#include "../phisics_2d.h"


class AddForceToPlayer : public entityx::System<AddForceToPlayer>
{
public:
	AddForceToPlayer();

	void update(entityx::EntityManager & en, entityx::EventManager &ev, double dt);

	~AddForceToPlayer();

private:

};