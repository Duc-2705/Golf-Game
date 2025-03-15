#pragma once

#include "Vector2D.h"
#include "TextureManager..h"
#include <vector>

class Obstacle
{
private:
	SDL_Texture* texObstacle;

	SDL_Rect srcObstacle;
	SDL_FRect destObstacle;

	std::string tag; // Shape obstacle

public:
	std::vector<std::pair<Vector2D, Vector2D>> planes; //Vector chua nhung mp cua obstacle

	float OBSTACLE_WIDTH;
	float OBSTACLE_HEIGHT;

	Vector2D position;
	Vector2D PointOnPlane; //Diem thuoc mp
	Vector2D normal; //Vector phap tuyen cua mpn co do dai = 1

	Obstacle(const std::string tag);
	~Obstacle();

	void init();

	void update();

	void render();
};