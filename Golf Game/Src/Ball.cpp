#include "Ball.h"
#include "TextureManager..h"
#include "Game.h"

Ball::Ball() {}

Ball::~Ball()
{
	delete cursor;
	SDL_DestroyTexture(texBall);
}

void Ball::init()
{
	texBall = TextureManager::LoadTexture("assets/BouncingBall.png");

	TextureManager::setSrcRect(texBall, srcBall);

	cursor = new Cursor();

	velocity.Zero();
	acceleration.Zero();
	
	position.x = 300.0f;
	position.y = 300.0f;

	destBall.w = static_cast<float>(BALL_WIDTH);
	destBall.h = static_cast<float>(BALL_HEIGHT);
}

void Ball::update()
{
	destBall.x = position.x;
	destBall.y = position.y;

	cursor->handleEvents();

	if (cursor->isPulling())
	{
		velocity = cursor->Force() * (-1);
		std::cout << cursor->Force() << std::endl;
	}

	acceleration.x = (velocity.x > 0) ? FRICTION : - FRICTION; // acceleration luon nguoc dau voi velocity
	acceleration.y = (velocity.y > 0) ? FRICTION : - FRICTION;

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
		position.x = static_cast<float> ( WINDOW_WIDTH - destBall.w);
		velocity.x *= REFLECT; //Doi chieu va giam nang luong
	}
	else if (position.x < 0)
	{
		position.x = 0.0f;
		velocity.x *= REFLECT;
	}

	if (position.y + destBall.h > WINDOW_HEIGHT)
	{
		position.y = static_cast<float> (WINDOW_HEIGHT - destBall.h);
		velocity.y *= REFLECT;
	}
	else if (position.y < 0)
	{
		position.y = 0.0f;
		velocity.y *= REFLECT;
	}	

}

void Ball::render()
{
	TextureManager::Draw(texBall, srcBall, destBall);
}