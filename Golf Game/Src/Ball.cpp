#include "Ball.h"
#include "TextureManager..h"
#include "Game.h"

Ball::Ball() {}

Ball::~Ball()
{
	SDL_DestroyTexture(texBall);
}

void Ball::init()
{
	texBall = TextureManager::LoadTexture("assets/ball.png");

	TextureManager::setSrcRect(texBall, srcBall);

	velocity.x = 400;
	velocity.y = 500;

	acceleration.x = (velocity.x > 0) ? FRICTION : - FRICTION; // acceleration luon nguoc dau voi velocity
	acceleration.y = (velocity.y > 0) ? FRICTION : - FRICTION;
	
	position.x = 0;
	position.y = 0;

	destBall.w = BALL_HEIGHT;
	destBall.h = BALL_HEIGHT;
}

void Ball::update()
{
	destBall.x = static_cast<int>(position.x);
	destBall.y = static_cast<int>(position.y);

	std::cout << velocity << std::endl;

}

void Ball::motion()
{
	if (velocity.x > 0)
	{
		velocity.x += acceleration.x * dTime;
		if (velocity.x < 0) velocity.x = 0.0f;
	}
	else if (velocity.x < 0)
	{
		velocity.x += acceleration.x * dTime;
		if (velocity.x > 0) velocity.x = 0.0f;
	}

	if (velocity.y > 0)
	{
		velocity.y += acceleration.y * dTime;
		if (velocity.y < 0) velocity.y = 0.0f;
	}
	else if (velocity.y < 0)
	{
		velocity.y += acceleration.y * dTime;
		if (velocity.y > 0) velocity.y = 0.0f;
	}

	position += (velocity * dTime);

	if (position.x + destBall.w > WINDOW_WIDTH)
	{
		velocity.x = 0;
		position.x = WINDOW_WIDTH - destBall.w;
	}
	else if (position.x < 0)
	{
		velocity.x = 0;
		position.x = 0;
	}

	if (position.y + destBall.h > WINDOW_HEIGHT)
	{
		velocity.y = 0;
		position.y = WINDOW_HEIGHT - destBall.h;
	}
	else if (position.y < 0)
	{
		velocity.y = 0;
		position.y = WINDOW_HEIGHT;
	}	

}

void Ball::render()
{
	TextureManager::Draw(texBall, srcBall, destBall);
}