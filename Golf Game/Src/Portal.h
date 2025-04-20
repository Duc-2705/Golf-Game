#pragma once

#include "Game.h"

class Portal
{
private:
	SDL_Texture* texPortal;
	SDL_Rect srcPortal;
	SDL_FRect destPortal;

	const int speed = 150;
	const int frames = 6;
	const int row = 2;
	const int column = 3;

public:
	Vector2D position;

	float PORTAL_WIDTH;
	float PORTAL_HEIGHT;

	Portal(const char* path, const float& x, const float& y, const float& w, const float& h);
	~Portal();

	void init();
	void update();
	void render();
};