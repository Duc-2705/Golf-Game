#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle()
{

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

	normal.i = - destObstacle.h / Vector2D::getMagnitude(destObstacle.w, destObstacle.h); //Vector don vi cua normal chieu len Ox
	normal.j = destObstacle.w / Vector2D::getMagnitude(destObstacle.w, destObstacle.h); //Vector don vi cua normal chieu len Oy

	//position.x = static_cast<float>(Game::WINDOW_WIDTH - destObstacle.w) - 100.0f;

	position.x = 100.0f;
	position.y = 100.0f;
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
