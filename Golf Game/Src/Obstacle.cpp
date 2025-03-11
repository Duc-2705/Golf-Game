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

	destObstacle.w = 400.0f;
	destObstacle.h = 200.0f;

	normal.i = - destObstacle.h / Vector2D::getMagnitude(destObstacle.w, destObstacle.h); //Vector don vi cua normal chieu len Ox
	normal.j = destObstacle.w / Vector2D::getMagnitude(destObstacle.w, destObstacle.h); //Vector don vi cua normal chieu len Oy

	position.x = static_cast<float>(Game::WINDOW_WIDTH - destObstacle.w);
	position.y = 0.0f;
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
