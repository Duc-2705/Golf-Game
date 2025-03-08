#include "Game.h"
#include "TextureManager..h"
#include "Ball.h"

Game::Game() {}
Game::~Game() {}

Ball* ball = new Ball();
int xMouse, yMouse;

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
			SDL_SetRenderDrawColor(renderer, 255, 255, 255 ,255);
		}

		isRunning = true;
	}

	ball->init();
}

void Game::handleEvents()
{
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&xMouse, &yMouse);
		std::cout << xMouse << " " << yMouse << std::endl;
		break;
	case SDL_MOUSEBUTTONUP:
		SDL_GetMouseState(&xMouse, &yMouse);
		std::cout << xMouse << " " << yMouse << std::endl;
		break;
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;
	}
}

void Game::update()
{
	ball->update();
	ball->motion();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	ball->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete ball;
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}
