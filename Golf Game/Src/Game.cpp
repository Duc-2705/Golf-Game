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

std::vector<Obstacle*> Game::obstacles = { obstacle1, obstacle2, obstacle3 };

Ball* ball = new Ball(Map::MAP_WIDTH / 2 - Ball::BALL_WIDTH /2, Map::MAP_HEIGHT / 2 - Ball::BALL_HEIGHT / 2, Game::obstacles);

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
SDL_FRect Game::camera = { 0.0f , 0.0f , Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT };

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

	map->LoadMap("assets/TileMap2.txt", 50, 40);

	for (auto& obstacle : obstacles) obstacle->init();

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

	for (auto& obstacle : obstacles) obstacle->update();

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
	
	for (auto& tile : map->tiles) tile->render();

	hole->render();

	for (auto& obstacle : obstacles) obstacle->render();

	if (!win) ball->render();

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	delete ball;
	delete hole;

	for (auto& obstacle : obstacles) delete obstacle;

	Mix_FreeChunk(chunkHit);
	Mix_FreeChunk(chunkDrop);
	Mix_FreeChunk(chunkCollide);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_Quit();
	SDL_Quit();
}
