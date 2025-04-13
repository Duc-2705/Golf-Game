#pragma once

#include "Cursor.h"
#include "Game.h"
#include "Vector2D.h"
#include "Obstacle.h"

class Cursor;

class Ball
{
private:
	const float dTime = 0.016f; //thoi gian 1 frame
	const float FRICTION = -80.0f; //giam toc do ma sat
	const float LOSS = 0.5f; // giam nang luong do va cham
	
	const int MAX_VELOCITY = 150;
	const int MAX_VOLUME = 128;

	const float LERP_SPEED = 0.1f;

	SDL_Rect srcBall;
	SDL_FRect destBall;

	SDL_Texture* texBall = nullptr;

	Cursor* cursor;

	std::vector<Obstacle*> obstacles;

	std::vector<bool> isAbleToCollide;

	void playChunk(Mix_Chunk* chunk,const float& veloMag);
	void motion();
	void collisionHandling();

public:
	Vector2D position;
	Vector2D velocity;
	Vector2D center;

	float radius;

	static const int BALL_WIDTH = 30;
	static const int BALL_HEIGHT = 30;

	Ball(const float& xPos, const float& yPos, const std::vector<Obstacle*>& obstacles);
	~Ball();

	void init();
	void handleEvent(SDL_Event& event);
	void update();
	void render();
	void updateCamera();
	void reset(const float& xPos, const float& yPos);
	bool stop();
};