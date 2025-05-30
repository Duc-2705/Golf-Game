#pragma once

#include "Vector2D.h"
#include "TextureManager..h"
#include "Ball.h"

class Hole
{
private:
	SDL_Texture* texHole = nullptr;

	SDL_Rect srcHole;
	SDL_FRect destHole;

public:
	const float HOLE_WIDTH = Ball::BALL_WIDTH;
	const float HOLE_HEGHT = Ball::BALL_HEIGHT;

	Vector2D position;

	Hole(const float& x, const float& y);
	~Hole() { SDL_DestroyTexture(texHole); };

	void init();
	void update();
	void render();
};