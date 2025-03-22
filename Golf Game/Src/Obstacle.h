#pragma once

#include "Vector2D.h"
#include "TextureManager..h"
#include <vector>

struct Plane
{
	Vector2D normal;
	Vector2D endPoint1;
	Vector2D endPoint2;

	Plane(Vector2D endPoint1, Vector2D endPoint2)
	{
		this->endPoint1.x = endPoint1.x;
		this->endPoint1.y = endPoint1.y;

		this->endPoint2.x = endPoint2.x;
		this->endPoint2.y = endPoint2.y;

		normal.normalize(endPoint1.y - endPoint2.y, endPoint2.x - endPoint1.x);
	}
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
														//voi first la vector normal, second là position diem thuoc mp

	float OBSTACLE_WIDTH;
	float OBSTACLE_HEIGHT;

	Vector2D position;

	Vector2D endPoint1; //Diem thuoc mp
	Vector2D endPoint2;

	Vector2D normal; //Vector phap tuyen cua mpn co do dai = 1

	Obstacle(const std::string shape , float x, float y, float w, float h);
	~Obstacle();

	void init();

	void update();

	void render();
};