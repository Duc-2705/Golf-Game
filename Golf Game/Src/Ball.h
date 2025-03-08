#pragma once

#include "Game.h"

const int BALL_WIDTH = 64;
const int BALL_HEIGHT = 64;

class Ball
{
private:
	int xpos, ypos;
	SDL_Texture* texBall = nullptr;
	SDL_Rect srcBall, destBall;
public:
	Ball();
	~Ball();

	void init();

	void update();

	void render();
};