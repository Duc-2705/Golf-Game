#include "Hole.h"

void Hole::init()
{
	texHole = TextureManager::LoadTexture("assets/Hole.png");

	TextureManager::setSrcRect(texHole, srcHole);

	position.x = static_cast<float>(Game::WINDOW_WIDTH / 2 - Ball::BALL_HEIGHT / 2);
	position.y = 100.0f;

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