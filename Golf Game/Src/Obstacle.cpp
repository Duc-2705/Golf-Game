#include "Obstacle.h"
#include "Game.h"

Obstacle::Obstacle(const std::string& shape, const float& x, const float& y, const float& w, const float& h)
{
	this->shape = shape;
	position.x = x;
	position.y = y;

	OBSTACLE_WIDTH = w;
	OBSTACLE_HEIGHT = h;
}

Obstacle::~Obstacle()
{
	SDL_DestroyTexture(texObstacle);
}

void Obstacle::init()
{

	destObstacle.w = OBSTACLE_WIDTH;
	destObstacle.h = OBSTACLE_HEIGHT;

	normal.Zero();

	if (shape == "Triangle")
	{
		texObstacle = TextureManager::LoadTexture("assets/TriangleObstacle.png");

		TextureManager::setSrcRect(texObstacle, srcObstacle);

		//Canh huyen
		planes.push_back({ Vector2D{position.x, position.y},
						Vector2D{position.x + OBSTACLE_WIDTH, position.y + OBSTACLE_HEIGHT} });

		//Canh goc vuong trai
		planes.push_back({ Vector2D{position.x + OBSTACLE_WIDTH, position.y + OBSTACLE_HEIGHT},
						Vector2D{position.x + OBSTACLE_WIDTH, position.y} });

		//Canh goc vuong tren
		planes.push_back({ Vector2D{position.x + OBSTACLE_WIDTH, position.y},
						Vector2D{position.x, position.y} });
	}
	
	else if (shape == "Rectangle")
	{
		texObstacle = TextureManager::LoadTexture("assets/RectangleObstacle.png");

		TextureManager::setSrcRect(texObstacle, srcObstacle);

		//Canh tren
		planes.push_back({ Vector2D{position.x, position.y},
						Vector2D{position.x + OBSTACLE_WIDTH, position.y} });

		//Canh phai
		planes.push_back({ Vector2D{position.x + OBSTACLE_WIDTH, position.y},
						Vector2D{position.x + OBSTACLE_WIDTH, position.y + OBSTACLE_HEIGHT} });

		//Canh duoi
		planes.push_back({ Vector2D{position.x + OBSTACLE_WIDTH, position.y + OBSTACLE_HEIGHT},
						Vector2D{position.x, position.y + OBSTACLE_HEIGHT} });

		//Canh trai
		planes.push_back({ Vector2D{position.x, position.y + OBSTACLE_HEIGHT},
						Vector2D{position.x, position.y} });
	}
}

void Obstacle::update()
{
	destObstacle.x = position.x;
	destObstacle.y = position.y;
}

void Obstacle::render()
{
	TextureManager::Draw(texObstacle, srcObstacle, destObstacle);
}
