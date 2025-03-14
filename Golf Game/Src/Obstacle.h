#pragma once

#include "Vector2D.h"
#include "TextureManager..h"

class Obstacle
{
private:
	SDL_Texture* texObstacle;

	SDL_Rect srcObstacle;
	SDL_FRect destObstacle;

public:

	float OBSTACLE_WIDTH;
	float OBSTACLE_HEIGHT;

	Vector2D position;
	Vector2D normal; //Vector phap tuyen cua mpn co do dai = 1

	Obstacle();
	~Obstacle();

	void init();

	void update();

	void render();
};