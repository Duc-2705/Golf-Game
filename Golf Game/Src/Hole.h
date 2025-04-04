#pragma once

#include "Vector2D.h"
#include "TextureManager..h"
#include "Ball.h"

class Hole
{
private:
	Vector2D velocity;
	
	float iDirect = 0.0f, jDirect = 0.0f;
	float speed = 0.0f;

	SDL_Texture* texHole = nullptr;

	SDL_Rect srcHole;
	SDL_FRect destHole;

	void motion();

public:
	Vector2D position;

	Hole(const float& iDirect, const float& jDirect, const float& speed) : iDirect(iDirect), jDirect(jDirect), speed(speed) {};
	~Hole() { SDL_DestroyTexture(texHole); };

	void init();
	void update();
	void render();
};