#pragma once

#include "Cursor.h"
#include "Game.h"
#include "Vector2D.h"

class Ball
{
private:
	const int BALL_WIDTH = 30.0;
	const int BALL_HEIGHT = 30.0;

	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;

	const float dTime = 0.016f; //thoi gian 1 frame
	const float FRICTION = -80.0f; //Ma sat, giam toc
	const float REFLECT = -0.5f; // Phan xa va giam nang luong

	SDL_Rect srcBall;
	SDL_FRect destBall;

	SDL_Texture* texBall = nullptr;

	Cursor* cursor = nullptr;

public:
	Ball();
	~Ball();

	void init();

	void update();

	void motion();

	void render();
};