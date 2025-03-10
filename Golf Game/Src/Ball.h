#pragma once

#include "Cursor.h"
#include "Game.h"
#include "Vector2D.h"

class Ball
{
private:

	Vector2D velocity;

	const float dTime = 0.016f; //thoi gian 1 frame
	const float FRICTION = -80.0f; //giam toc do ma sat
	const float LOSS = 0.5f; // giam nang luong do va cham

	SDL_Rect srcBall;
	SDL_FRect destBall;

	SDL_Texture* texBall = nullptr;

	Cursor* cursor = nullptr;

public:
	Vector2D position;

	static const int BALL_WIDTH = 30;
	static const int BALL_HEIGHT = 30;

	Ball();
	~Ball();

	void init();

	void update();

	void motion();

	void render();
};