#pragma once

#include "Ball.h"
#include "TextureManager..h"
#include "Game.h"

class Arrow
{
private:
	SDL_Texture* texArrow;

	SDL_Rect srcArrow;
	SDL_FRect destArrow;

	SDL_FPoint centerRotate;

	double angle;
	const float SCALE = 1;

public:
	Arrow();
	~Arrow();

	void init();
	void update();
	void setAngle(double angle);
	void setRange(float mag);
	void render();
};