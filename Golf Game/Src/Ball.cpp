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
	
	position.x = static_cast<float>(Game::WINDOW_WIDTH/2 - BALL_WIDTH/2);
	position.y = static_cast<float>(Game::WINDOW_HEIGHT/2 -BALL_HEIGHT/2);

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
		velocity.magnitude = cursor->Force().magnitude; // Do lon cua Force

		// Vector don vi cua Force chieu len Ox
		velocity.i = (cursor->Force().magnitude) ? - (cursor->Force().x / cursor->Force().magnitude) : 0; // Tranh viec chia cho 0

		// Vector don vi cua Force chieu len Oy
		velocity.j = (cursor->Force().magnitude) ? - (cursor->Force().y / cursor->Force().magnitude) : 0; // Tranh viec chia cho 0
	}

}

void Ball::motion()
{
	if (velocity.magnitude > 0)
	{
		velocity.magnitude += FRICTION * dTime; // Giam do lon cua van toc
		if (velocity.magnitude < 0) velocity.Zero();
	}

	position.x += velocity.i * velocity.magnitude * dTime;
	position.y += velocity.j * velocity.magnitude * dTime;

	if (position.x + destBall.w > Game::WINDOW_WIDTH)
	{
		position.x = static_cast<float> ( Game::WINDOW_WIDTH - destBall.w);
		velocity.i *= -1.0f; //Doi chieu do va cham
		velocity.magnitude *= LOSS; //Giam nang luong do va cham
	}
	else if (position.x < 0)
	{
		position.x = 0.0f;
		velocity.i *= -1.0f;
		velocity.magnitude *= LOSS;
	}

	if (position.y + destBall.h > Game::WINDOW_HEIGHT)
	{
		position.y = static_cast<float> (Game::WINDOW_HEIGHT - destBall.h);
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;
	}
	else if (position.y < 0)
	{
		position.y = 0.0f;
		velocity.j *= -1.0f;
		velocity.magnitude *= LOSS;
	}	

}

void Ball::render()
{
	TextureManager::Draw(texBall, srcBall, destBall);
}