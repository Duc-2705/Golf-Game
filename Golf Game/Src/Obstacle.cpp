#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle(const std::string shape, int x, int y, int w, int h)
{
	this->shape = shape;
	position.x = x;
	position.y = y;

	OBSTACLE_WIDTH = w;
	OBSTACLE_HEIGHT = h;
}

Obstacle::~Obstacle()
{
	SDL_DestroyTexture(texObstacle);
}

void Obstacle::init()
{

	destObstacle.w = OBSTACLE_WIDTH;
	destObstacle.h = OBSTACLE_HEIGHT;

	if (shape == "Triangle")
	{
		texObstacle = TextureManager::LoadTexture("assets/TriangleObstacle.png");

		TextureManager::setSrcRect(texObstacle, srcObstacle);

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
	
	else if (shape == "Rectangle")
	{
		texObstacle = TextureManager::LoadTexture("assets/RectangleObstacle.png");

		TextureManager::setSrcRect(texObstacle, srcObstacle);

		normal.i = 0;
		normal.j = 1;

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
		PointOnPlane.y = position.y + OBSTACLE_HEIGHT;

		planes.push_back({ normal, PointOnPlane });

		normal.i = 1;
		normal.j = 0;

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
