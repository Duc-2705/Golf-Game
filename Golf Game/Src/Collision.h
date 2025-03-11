#pragma once

#include "Ball.h"
#include "Obstacle.h"

class Collision
{
public:
	static float distanceToLine(const Ball& ball, const Obstacle& obstacle);

	static bool checkCollision(const Ball& ball, const Obstacle& obstacle);
};