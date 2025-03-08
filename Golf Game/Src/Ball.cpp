#include "Ball.h"
#include "TextureManager..h"
#include "Game.h"
#include "Vector2D.h"

Ball::Ball() {}

Ball::~Ball()
{
	SDL_DestroyTexture(texBall);
}

void Ball::init()
{
	texBall = TextureManager::LoadTexture("assets/ball.png");

	TextureManager::setSrcRect(texBall, srcBall);
	
	xpos = ypos = 0;

	destBall.w = BALL_HEIGHT;
	destBall.h = BALL_HEIGHT;
}

void Ball::update()
{
	destBall.x = xpos;
	destBall.y = ypos;
	
}

void Ball::render()
{
	TextureManager::Draw(texBall, srcBall, destBall);
}