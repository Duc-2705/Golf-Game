#include "Collision.h"

float Collision::distanceToLine(const Ball& ball, const Obstacle& obstacle) 
{
	//Khoang cach tu tam ball den duong thang mp obstacle
	return (obstacle.normal.i * (ball.center.x - obstacle.position.x) +
		obstacle.normal.j * (ball.center.y - obstacle.position.y));
}

bool Collision::checkProjection(const Ball& ball, const Obstacle& obstacle)
{
	float distance = Collision::distanceToLine(ball, obstacle);

	float xProj = ball.center.x - obstacle.normal.i * distance;
	float yProj = ball.center.y - obstacle.normal.j * distance;

	return (xProj >= obstacle.position.x && xProj <= obstacle.position.x + obstacle.OBSTACLE_WIDTH &&
		yProj >= obstacle.position.y && yProj <= obstacle.position.y + obstacle.OBSTACLE_HEIGHT);

	// Neu tam qua bong nam ngoai nhung 1 phan cua no van cham voi obstacle
	
	/*float mag = sqrt((xProj - ball.center.x) * (xProj - ball.center.x) + (yProj - ball.center.y) * (yProj - ball.center.y));

	float xMinProj = ball.center.x + ball.radius * (xProj - ball.center.x) / mag;
	float yMinProj = ball.center.y + ball.radius * (yProj - ball.center.y) / mag;

	return (xMinProj >= obstacle.position.x && xMinProj <= obstacle.position.x + obstacle.OBSTACLE_WIDTH &&
		yMinProj >= obstacle.position.y && yMinProj <= obstacle.position.y + obstacle.OBSTACLE_HEIGHT);*/
}

bool Collision::checkCollision(const Ball& ball, const Obstacle& obstacle)
{
	//So sanh khoang cach tu tam ball den duong thang mp obstacle voi ban kinh ball
	return checkProjection (ball, obstacle) && fabs(Collision::distanceToLine(ball, obstacle)) <= ball.radius;
}