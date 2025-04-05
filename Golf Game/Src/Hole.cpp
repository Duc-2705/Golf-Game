#include "Hole.h"
#include "Map.h"

void Hole::init()
{
	texHole = TextureManager::LoadTexture("assets/Hole.png");

	TextureManager::setSrcRect(texHole, srcHole);

	position.x = static_cast<float>(Map::MAP_WIDTH / 2 - Ball::BALL_HEIGHT / 2);
	position.y = 100.0f;

	velocity.i = iDirect;
	velocity.j = jDirect;

	destHole.w = Ball::BALL_WIDTH;
	destHole.h = Ball::BALL_HEIGHT;
}

void Hole::update()
{
	destHole.x = position.x;
	destHole.y = position.y;

	this->motion();
}

void Hole::motion()
{
	position.x += velocity.i * speed;
	position.y += velocity.j * speed;

	if (position.x + destHole.w > Game::WINDOW_WIDTH)
	{
		position.x = static_cast<float> (Game::WINDOW_WIDTH - destHole.w);
		velocity.i *= -1.0f; //Doi chieu do va cham
	}
	else if (position.x < 0)
	{
		position.x = 0.0f;
		velocity.i *= -1.0f;
	}

	if (position.y + destHole.h > Game::WINDOW_HEIGHT)
	{
		position.y = static_cast<float> (Game::WINDOW_HEIGHT - destHole.h);
		velocity.j *= -1.0f;
	}
	else if (position.y < 0)
	{
		position.y = 0.0f;
		velocity.j *= -1.0f;
	}
}

void Hole::render()
{
	TextureManager::Draw(texHole, srcHole, destHole);
}