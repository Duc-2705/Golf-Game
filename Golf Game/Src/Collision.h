#pragma once

#include "Ball.h"
#include "Obstacle.h"

class Collision
{
public:
	static float distanceToLine(const Ball& ball, const std::pair <Vector2D, Vector2D>& plane);

	static bool checkProjection(const Ball& ball, const Obstacle& obstacle, const std::pair<Vector2D, Vector2D>& plane);

	static int checkCollision(const Ball& ball,const Obstacle& obstacle);
};