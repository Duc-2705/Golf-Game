#pragma once

#include "Ball.h"
#include "Obstacle.h"
#include "Vector2D.h"

class Collision
{
public:
	static float distanceToLine(const Ball& ball, const Plane& plane);

	static bool checkProjection(const Ball& ball, const Obstacle& obstacle, const Plane& plane);

	static int checkCollision(const Ball& ball, Obstacle& obstacle);
};