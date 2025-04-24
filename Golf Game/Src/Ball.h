#pragma once

#include "Cursor.h"
#include "Game.h"
#include "Vector2D.h"
#include "Obstacle.h"
#include "Portal.h"

class Cursor;


class Ball
{
private:
	const float dTime = 0.016f; //thoi gian 1 frame
	const float LOSS = 0.5f; // giam nang luong do va cham
	float FRICTION = -80.0f; //giam toc do ma sat
	
	const int MAX_VELOCITY = 150;
	const int MAX_VOLUME = 128;

	const float LERP_SPEED = 0.1f;

	SDL_Rect srcBall;
	SDL_FRect destBall;

	SDL_Texture* texBall = nullptr;

	std::vector<bool> isAbleToCollide;
	bool waterDrop = false;

	void playChunk(Mix_Chunk* chunk,const float& veloMag, const int& loops);
	void motion();
	void collisionHandling();
	void teleport();
	void handleCollisionTiles();

public:
	Vector2D position;
	Vector2D velocity;
	Vector2D center;

	Cursor* cursor;

	float radius;

	static const int BALL_WIDTH = 30;
	static const int BALL_HEIGHT = 30;

	Ball(const float& xPos, const float& yPos);
	~Ball();

	void init();
	void handleEvent(SDL_Event& event);
	void update();
	void render();

	void updateCamera();
	void reset(const float& xPos, const float& yPos);
	bool stop();
	bool checkWaterDrop();
};