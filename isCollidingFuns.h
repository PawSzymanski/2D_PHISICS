#pragma once
#include <entityx\entityx.h>
#include <SFML\Graphics.hpp>
#include <cmath>

#include "components.h"

bool isColliding(entityx::Entity en1, entityx::Entity en2);
