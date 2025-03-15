#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle(const std::string tag)
{
	this->tag = tag;
}

Obstacle::~Obstacle()
{
	SDL_DestroyTexture(texObstacle);
}

void Obstacle::init()
{
	texObstacle = TextureManager::LoadTexture("assets/obstacle.png");

	TextureManager::setSrcRect(texObstacle, srcObstacle);

	OBSTACLE_WIDTH = 400.0f;
	OBSTACLE_HEIGHT = 200.0f;

	destObstacle.w = OBSTACLE_WIDTH;
	destObstacle.h = OBSTACLE_HEIGHT;

	position.x = 400.0f;
	position.y = 400.0f;

	if (tag == "Triangle")
	{
		normal.i = -destObstacle.h / Vector2D::getMagnitude(destObstacle.w, destObstacle.h); //Vector don vi cua normal chieu len Ox
		normal.j = destObstacle.w / Vector2D::getMagnitude(destObstacle.w, destObstacle.h); //Vector don vi cua normal chieu len Oy

		PointOnPlane.x = position.x;
		PointOnPlane.y = position.y;

		planes.push_back({ normal, PointOnPlane });

		normal.i = 1;
		normal.j = 0;

		PointOnPlane.x = position.x + OBSTACLE_WIDTH;
		PointOnPlane.y = position.y;

		planes.push_back({ normal, PointOnPlane });

		normal.i = 0;
		normal.j = 1;

		PointOnPlane.x = position.x;
		PointOnPlane.y = position.y;

		planes.push_back({ normal, PointOnPlane });
	}
}

void Obstacle::update()
{
	destObstacle.x = position.x;
	destObstacle.y = position.y;
}

void Obstacle::render()
{
	TextureManager::Draw(texObstacle, srcObstacle, destObstacle);
}
