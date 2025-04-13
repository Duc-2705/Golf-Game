#pragma once

#include "Game.h"
#include "Cursor.h"

class PowerBar
{
private:

	SDL_Texture* texBar;
	SDL_Rect srcBar;
	SDL_FRect destBar;

	SDL_Texture* texMaxBar;
	SDL_Rect srcMaxBar;
	SDL_FRect destMaxBar;

	Cursor* cursor;

public:
	float power;

	PowerBar(Cursor* cursor);
	~PowerBar();

	void init();
	void update();
	void render();
};