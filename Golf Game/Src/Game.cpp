#include "Game.h"
#include "TextureManager..h"
#include "Ball.h"
#include "Hole.h"

Game::Game() {}
Game::~Game() {}

Ball* ball = new Ball();
Hole* hole = new Hole();

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;

void Game::init(const char* title, int width, int height, bool fullscreen)
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

	ball->update();
	std::cout << std::fabs(ball->position.x - hole->position.x) << " " <<
				 std::fabs(ball->position.y - hole->position.y) << std::endl;
	
	if (std::fabs(ball->position.x - hole->position.x) <= 5  &&
		std::fabs(ball->position.y - hole->position.y) <= 5)
	{
		isRunning = false;
	}

	ball->motion();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	hole->render();
	ball->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete ball;
	delete hole;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
