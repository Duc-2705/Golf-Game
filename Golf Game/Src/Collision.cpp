#include "Collision.h"

float Collision::distanceToLine(const Ball& ball, const Plane& plane)
{
	return (plane.normal.i * (ball.center.x - plane.endPoint1.x) +
		plane.normal.j * (ball.center.y - plane.endPoint1.y));
}

bool Collision::checkProjection(const Ball& ball, const Plane& plane)
{
	float distance = Collision::distanceToLine(ball, plane);

	float xProj = ball.center.x - plane.normal.i * distance;
	float yProj = ball.center.y - plane.normal.j * distance;

	return (
		(plane.normal.j == 0 || xProj >= std::min(plane.endPoint1.x, plane.endPoint2.x) && xProj <= std::max(plane.endPoint1.x, plane.endPoint2.x)) &&
		(plane.normal.i == 0 || yProj >= std::min(plane.endPoint1.y, plane.endPoint2.y) && yProj <= std::max(plane.endPoint1.y, plane.endPoint2.y)));
}

bool Collision::checkCollisionPlane(const Ball& ball, const Plane& plane)
{
	return checkProjection(ball, plane) && std::fabs(distanceToLine(ball, plane)) <= ball.radius;
}

bool Collision::checkCollisionCorner(const Ball& ball, const Vector2D& point)
{
	return Vector2D::getMagnitude(ball.center.x - point.x, ball.center.y - point.y) <= ball.radius;
}
	
int Collision::checkCollisionObstacle(const Ball& ball, Obstacle& obstacle)
{
	for (int i = 0; i < (int) obstacle.planes.size(); i ++)
	{
		Plane plane = obstacle.planes[i];

		if (checkCollisionPlane(ball, plane))//Va cham canh
		{
			obstacle.normal.normalize(plane.endPoint1.y - plane.endPoint2.y, plane.endPoint2.x - plane.endPoint1.x); //Dn vi hoa

			return i;
		}
		else if (checkCollisionCorner(ball, plane.endPoint1)) //Va cham goc
		{
			//normal la vector tao boi center ball va position dinh cua obstacle tai goc do
			obstacle.normal.normalize(ball.center.x - plane.endPoint1.x, ball.center.y - plane.endPoint1.y); //Don vi hoa

			return i;
		}
	}
	return -1;
}

bool Collision::checkCollisionTile(const Ball* ball, const Tile* tile)
{
	return (ball->center.x >= tile->destTile.x && ball->center.x <= tile->destTile.x + tile->TILE_WIDTH &&
		ball->center.y >= tile->destTile.y && ball->center.y <= tile->destTile.y + tile->TILE_HEIGHT);
}