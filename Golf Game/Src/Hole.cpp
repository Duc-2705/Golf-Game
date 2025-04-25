#include "Hole.h"
#include "Map.h"

Hole::Hole(const float& x, const float& y)
{
	position.x = x;
	position.y = y;
}

void Hole::init()
{
	texHole = TextureManager::LoadTexture("assets/Hole.png");

	TextureManager::setSrcRect(texHole, srcHole);

	destHole.w = Ball::BALL_WIDTH;
	destHole.h = Ball::BALL_HEIGHT;
}

void Hole::update()
{
	destHole.x = position.x;
	destHole.y = position.y;
}

void Hole::render()
{
	TextureManager::Draw(texHole, srcHole, destHole);
}