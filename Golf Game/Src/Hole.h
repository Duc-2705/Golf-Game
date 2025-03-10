#pragma once

#include "Vector2D.h"
#include "TextureManager..h"
#include "Ball.h"

class Hole
{
private:
	Vector2D velocity;

	float speed = 0.0f;

	SDL_Texture* texHole = nullptr;

	SDL_Rect srcHole;
	SDL_FRect destHole;
public:
	Vector2D position;

	Hole(float speed) : speed(speed) {};
	~Hole() { SDL_DestroyTexture(texHole); };

	void init();

	void update();

	void motion();

	void render();
};