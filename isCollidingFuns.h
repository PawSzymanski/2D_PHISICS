#pragma once
#include <entityx\entityx.h>
#include <SFML\Graphics.hpp>
#include <cmath>

#include "components.h"
#include "Manifold.h"
#include "AutisticCmath.cpp"

void isCollidingCC(Manifold &man);
void isCollidingCP(Manifold &man);
void isCollidingPC(Manifold &man);
void isCollidingPP(Manifold &man);