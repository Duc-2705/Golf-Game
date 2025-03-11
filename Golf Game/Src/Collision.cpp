#include "Collision.h"

float Collision::distanceToLine(const Ball& ball, const Obstacle& obstacle) 
{
	//Khoang cach tu tam ball den duong thang mp obstacle
	return fabs(obstacle.normal.i * (ball.center.x - obstacle.position.x) +
		obstacle.normal.j * (ball.center.y - obstacle.position.y));
}

bool Collision::checkCollision(const Ball& ball, const Obstacle& obstacle)
{
	//So sanh khoang cach tu tam ball den duong thang mp obstacle voi ban kinh ball
	return Collision::distanceToLine(ball, obstacle) <= ball.radius;
}