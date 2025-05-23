#pragma once

#include "Vector2D.h"
#include "TextureManager..h"
#include <vector>

struct Plane
{
	Vector2D normal;
	Vector2D endPoint1;
	Vector2D endPoint2;

	Plane(Vector2D endPoint1, Vector2D endPoint2);
};

class Obstacle
{
private:
	SDL_Texture* texObstacle;

	SDL_Rect srcObstacle;
	SDL_FRect destObstacle;

	std::string shape; // Shape obstacle

public:
	std::vector<Plane> planes; //Vector chua nhung mp cua obstacle 

	float OBSTACLE_WIDTH;
	float OBSTACLE_HEIGHT;

	Vector2D position;

	Vector2D normal; //Vector phap tuyen cua mpn co do dai = 1

	Obstacle(const std::string& shape ,const float& x, const float& y, const float& w, const float& h);
	~Obstacle();

	void init();
	void update();
	void render();
};