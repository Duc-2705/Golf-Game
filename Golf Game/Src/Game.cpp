#include "Game.h"
#include "TextureManager..h"
#include "Ball.h"
#include "Hole.h"
#include "Obstacle.h"
#include "Collision.h"

Game::Game() {}
Game::~Game() {}

Hole* hole = new Hole (0,0,0);

Obstacle* obstacle1 = new Obstacle("Rectangle", 400, 200, 200, 100);
Obstacle* obstacle2 = new Obstacle("Triangle", 400, 100, 300, 100);
Obstacle* obstacle3 = new Obstacle("Triangle", 50, 500, 100, 100);

Ball* ball = new Ball(obstacle1, obstacle2, obstacle3);

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

void Game::init(const char* title, bool fullscreen)
{
	int flag = 0;
	if (fullscreen) flag = SDL_WINDOW_FULLSCREEN;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, flag);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 224, 189 ,255);
		}

		isRunning = true;
	}

	obstacle1->init();
	obstacle2->init();
	obstacle3->init();
	ball->init();
	hole->init();

}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	hole->update();
	obstacle1->update();
	obstacle2->update();
	obstacle3->update();

	if (!win)
	{
		ball->update();
	}
	
	if (!win &&
		std::fabs(ball->position.x - hole->position.x) <= 5  &&
		std::fabs(ball->position.y - hole->position.y) <= 5)
	{
		win = true;
		delete ball;
		ball = nullptr;
		std::cout << "Congratulation!!" << std::endl;
	}

	if (!win) ball->motion();
	
	hole->motion();

	//Collision::checkProjection(*ball, *obstacle);
}

void Game::render()
{
	SDL_RenderClear(renderer);

	hole->render();
	obstacle1->render();
	obstacle2->render();
	obstacle3->render();
	if (!win) ball->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete ball;
	delete hole;
	delete obstacle1;
	delete obstacle2;
	delete obstacle3;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
