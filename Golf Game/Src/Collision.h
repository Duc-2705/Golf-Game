#pragma once

#include "Ball.h"
#include "Obstacle.h"
#include "Vector2D.h"
#include "Tile.h"

class Collision
{
public:
	static float distanceToLine(const Ball& ball, const Plane& plane);

	static bool checkProjection(const Ball& ball, const Plane& plane);

	static bool checkCollisionCorner(const Ball& ball, const Vector2D& point);

	static bool checkCollisionPlane(const Ball& ball, const Plane& plane);

	static int checkCollisionObstacle(const Ball& ball, Obstacle& obstacle);

	static bool checkCollisionTile(const Ball* ball, const Tile* tile);
};