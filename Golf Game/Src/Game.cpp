#include "Game.h"
#include "TextureManager..h"
#include "Ball.h"
#include "Hole.h"
#include "Obstacle.h"
#include "Collision.h"
#include "Map.h"
#include "Button.h"
#include "Background.h"

Game::Game() {}
Game::~Game() {}

TTF_Font* Game::font = nullptr;

Map* map = new Map();

Background* background1;

Hole* hole = new Hole (0.0f, 0.0f, 0.0f);

Obstacle* obstacle1 = new Obstacle("Rectangle", 450.0f, 300.0f, 200.0f, 100.0f);
Obstacle* obstacle2 = new Obstacle("Triangle", 400.0f, 100.0f, 300.0f, 100.0f);
Obstacle* obstacle3 = new Obstacle("Triangle", 50.0f, 500.0f, 100.0f, 100.0f);

std::vector<Obstacle*> Game::obstacles = { obstacle1, obstacle2, obstacle3 };

Ball* ball = new Ball(Map::MAP_WIDTH / 2 - Ball::BALL_WIDTH /2, Map::MAP_HEIGHT / 2 - Ball::BALL_HEIGHT / 2, Game::obstacles);

Button* button1;
Button* button2;

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
SDL_FRect Game::camera = { 0.0f , 0.0f , Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT };

Mix_Chunk* Game::chunkHit = nullptr;
Mix_Chunk* Game::chunkDrop = nullptr;
Mix_Chunk* Game::chunkCollide = nullptr;

enum GameState { Menu, Playing, Pause, GameOver };
GameState currentState = Menu;

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

	if (TTF_Init() == -1) std::cout << "TTF_Init failed: " << TTF_GetError() << std::endl;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL2_mixer could not initialize!: " << Mix_GetError() << std::endl;
	}

	chunkHit = Mix_LoadWAV("sound/Hit.wav");
	chunkDrop = Mix_LoadWAV("sound/hole_drop.wav");
	chunkCollide = Mix_LoadWAV("sound/bass.wav");

	font = TTF_OpenFont("font/arial.ttf", 24);

	button1 = new Button("START", (Game::WINDOW_WIDTH - 100) * 0.5f, (Game::WINDOW_HEIGHT - 50) * 0.5f, 100.0f, 50.0f);
	button2 = new Button("PLAY AGAIN",(Game::WINDOW_WIDTH - 100) * 0.5f, (Game::WINDOW_HEIGHT - 50) * 0.5f, 100.0f, 50.0f);

	map->LoadMap("assets/TileMap2.txt", 50, 40);

	background1 = new Background("assets/MenuBg.png", 0.0f, 0.0f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
	background1->init();

	for (auto& obstacle : obstacles) obstacle->init();

	ball->init();
	hole->init();

	button1->init();
	button2->init();
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) isRunning = false;

		else if (currentState == Menu)
		{
			button1->handleEvent(event);
			if (button1->isPressed()) currentState = Playing;
		}

		else if (currentState == Playing)
		{	
			ball->handleEvent(event);

		}

		else if (currentState = GameOver)
		{
			button2->handleEvent(event);
			if (button2->isPressed())
			{
				currentState = Playing;
				ball->reset(Map::MAP_WIDTH / 2 - Ball::BALL_WIDTH / 2, Map::MAP_HEIGHT / 2 - Ball::BALL_HEIGHT / 2);
			}
		}
	}
}

void Game::update()
{
	if (currentState == Menu)
	{
		button1->update();
		background1->update();
	}

	else if (currentState == Playing)
	{
		hole->update();

		for (auto& obstacle : obstacles) obstacle->update();

		ball->update();

		if (std::fabs(ball->position.x - hole->position.x) <= 5.0f &&
			std::fabs(ball->position.y - hole->position.y) <= 5.0f)
		{
			Mix_PlayChannel(-1, chunkDrop, 0);

			std::cout << "Congratulation!!" << std::endl;
			currentState = GameOver;
		}
	}

	else if (currentState == GameOver)
	{
		button2->update();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	if (currentState == Menu)
	{
		background1->render();
		button1->render();
	}

	else if (currentState == Playing)
	{
		for (auto& tile : map->tiles) tile->render();

		hole->render();

		for (auto& obstacle : obstacles) obstacle->render();

		ball->render();
	}

	else if (currentState = GameOver)
	{
		for (auto& tile : map->tiles) tile->render();

		hole->render();

		for (auto& obstacle : obstacles) obstacle->render();

		button2->render();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	delete background1;
	delete ball;
	delete hole;
	delete button1;
	delete button2;

	for (auto& obstacle : obstacles) delete obstacle;

	Mix_FreeChunk(chunkHit);
	Mix_FreeChunk(chunkDrop);
	Mix_FreeChunk(chunkCollide);

	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
