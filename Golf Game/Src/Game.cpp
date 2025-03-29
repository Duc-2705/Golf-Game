#include "Game.h"
#include "TextureManager..h"
#include "Ball.h"
#include "Hole.h"
#include "Obstacle.h"
#include "Collision.h"
#include "Map.h"

Game::Game() {}
Game::~Game() {}

Map* map = new Map();

Hole* hole = new Hole (0.0f, 0.0f, 0.0f);

Obstacle* obstacle1 = new Obstacle("Rectangle", 450.0f, 300.0f, 200.0f, 100.0f);
Obstacle* obstacle2 = new Obstacle("Triangle", 400.0f, 100.0f, 300.0f, 100.0f);
Obstacle* obstacle3 = new Obstacle("Triangle", 50.0f, 500.0f, 100.0f, 100.0f);

Ball* ball = new Ball(obstacle1, obstacle2, obstacle3);

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
Mix_Chunk* Game::chunkHit = nullptr;
Mix_Chunk* Game::chunkDrop = nullptr;
Mix_Chunk* Game::chunkCollide = nullptr;

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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL2_mixer could not initialize!: " << Mix_GetError() << std::endl;
	}

	chunkHit = Mix_LoadWAV("sound/Hit.wav");
	chunkDrop = Mix_LoadWAV("sound/hole_drop.wav");
	chunkCollide = Mix_LoadWAV("sound/bass.wav");

	map->LoadMap("assets/TileMap1.txt", 25, 20);

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
		std::fabs(ball->position.x - hole->position.x) <= 5.0f  &&
		std::fabs(ball->position.y - hole->position.y) <= 5.0f)
	{
		Mix_PlayChannel(-1, chunkDrop, 0);

		win = true;
		delete ball;
		ball = nullptr;
		std::cout << "Congratulation!!" << std::endl;
	}
	
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	for (auto& tile : map->tiles)
	{
		tile->render();
	}

	hole->render();

	obstacle1->render();
	obstacle2->render();
	obstacle3->render();

	if (!win) ball->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	delete ball;
	delete hole;
	delete obstacle1;
	delete obstacle2;
	delete obstacle3;

	Mix_FreeChunk(chunkHit);
	Mix_FreeChunk(chunkDrop);
	Mix_FreeChunk(chunkCollide);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_Quit();
	SDL_Quit();
}
