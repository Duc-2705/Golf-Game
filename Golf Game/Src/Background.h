#pragma once

#include "Game.h"

class Background
{
private:
	SDL_Texture* texBg;

	SDL_Rect srcBg;
	SDL_FRect destBg;

public:
	Background(const char* path, const float& xPos, const float& yPos, const float& w, const float& h);
	~Background();

	void init();
	void update();
	void render();
};