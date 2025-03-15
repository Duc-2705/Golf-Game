#include "Collision.h"

float Collision::distanceToLine(const Ball& ball, const std::pair<Vector2D, Vector2D>& plane)
{
	return (plane.first.i * (ball.center.x - plane.second.x) +
		plane.first.j * (ball.center.y - plane.second.y));
}

bool Collision::checkProjection(const Ball& ball, const Obstacle& obstacle, const std::pair<Vector2D, Vector2D>& plane)
{
	float distance = Collision::distanceToLine(ball, plane);

	float xProj = ball.center.x - plane.first.i * distance;
	float yProj = ball.center.y - plane.second.j * distance;

	return (
		(plane.first.j == 0 || xProj >= plane.second.x && xProj <= plane.second.x + obstacle.OBSTACLE_WIDTH) &&
		(plane.first.i == 0 || yProj >= plane.second.y && yProj <= plane.second.y + obstacle.OBSTACLE_HEIGHT));
}

int Collision::checkCollision(const Ball& ball, const Obstacle& obstacle)
{
	for (int i = 0; i < (int) obstacle.planes.size(); i ++)
	{

		if (checkProjection(ball,obstacle, obstacle.planes[i]) && std::fabs(distanceToLine(ball, obstacle.planes[i])) <= ball.radius) return i;
	}
	return -1;
}