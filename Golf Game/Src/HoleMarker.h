#pragma once

#include "Game.h"

class HoleMarker
{
private:
	SDL_FPoint markerPos;

public:
	HoleMarker();
	~HoleMarker();

	bool checkHoleInCamera();
	void update();
	void render();
};