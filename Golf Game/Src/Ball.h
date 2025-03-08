#pragma once

#include "Game.h"
#include "Vector2D.h"


class Ball
{
private:
	const int BALL_WIDTH = 64;
	const int BALL_HEIGHT = 64;

	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;

	const float dTime = 0.016f; //thoi gian 1 frame
	const float FRICTION = -80.0f; //Ma sat

	SDL_Rect srcBall, destBall;
	SDL_Texture* texBall = nullptr;
public:
	Ball();
	~Ball();

	void init();

	void update();

	void render();
};