#pragma once

#include "Ball.h"
#include "TextureManager..h"
#include "Game.h"

class Ball;

class Arrow
{
private:
	SDL_Texture* texArrow;

	SDL_Rect srcArrow;
	SDL_FRect destArrow;

	SDL_FPoint centerRotate;

	double angle;

	const float SCALE = 1;

	Ball* ball;
public:
	Arrow(Ball* ball);
	~Arrow();

	void init();

	void update();

	void setAngle(double angle);

	void setRange(float mag);

	void render();
};