#include "Arrow.h"

Arrow::Arrow(Ball* ball)
{
	this->ball = ball;
}

Arrow::~Arrow()
{
	SDL_DestroyTexture(texArrow);
}

void Arrow::init()
{
	texArrow = TextureManager::LoadTexture("assets/arrow.png");

	TextureManager::setSrcRect(texArrow, srcArrow);

	destArrow.w = 0.0f;
	destArrow.h = 40.0f;

	centerRotate.x = 0;
	centerRotate.y = destArrow.h / 2;

	angle = 0;
}

void Arrow::update()
{
	destArrow.x = ball->center.x;
	destArrow.y = ball->center.y - destArrow.h/2;
}

void Arrow::setAngle(double angle)
{
	this->angle = angle;
}

void Arrow::setRange(float mag)
{
	destArrow.w = mag * SCALE;
	if (destArrow.w > 50.0f) destArrow.w = 50.0f;
}

void Arrow::render()
{
	SDL_RenderCopyExF(Game::renderer, texArrow, &srcArrow, &destArrow, angle, &centerRotate, SDL_FLIP_NONE);
}

