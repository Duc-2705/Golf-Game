#include "Game.h"
#include "TextureManager..h"

Game::Game() {}
Game::~Game() {}

SDL_Texture* Game::texture = nullptr;

SDL_Renderer* Game::renderer = nullptr;

void Game::init(const char* title, int width, int height, bool fullscreen)
{
	int flag = 0;
	if (fullscreen) flag = SDL_WINDOW_FULLSCREEN;
	
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flag);
		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		}

		isRunning = true;
	}
	
	texture = TextureManager::LoadTexture("assets/ball.png");
	TextureManager::setSrcRect(texture, srcRect);
	destRect.x = destRect.y = 300;
	destRect.w = destRect.h = 64;

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

}

void Game::render()
{
	SDL_RenderClear(renderer);
	

	TextureManager::Draw(Game::texture, srcRect, destRect);

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyTexture(texture);
	SDL_Quit();
}
