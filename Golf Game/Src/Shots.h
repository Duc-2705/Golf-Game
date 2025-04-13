#pragma once

#include "Game.h"

class Shots
{
private:
	SDL_Texture* texShots;
	SDL_Rect srcShots;
	SDL_FRect destShots;

	const int SHOT_WIDTH = 64;

public:
	Shots();
	~Shots();

	void update();
	void render();
};