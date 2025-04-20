#include "Game.h"
#include "TextureManager..h"
#include "Ball.h"
#include "Hole.h"
#include "Obstacle.h"
#include "Collision.h"
#include "Map.h"
#include "Button.h"
#include "Background.h"
#include "PowerBar.h"
#include "Shots.h"
#include "Portal.h"

Game::Game() {}
Game::~Game() {}

TTF_Font* Game::font = nullptr;

Map* map = new Map();

int Game::remainingShots = 3;

Background* MenuBg, *WinStateBg;

Hole* hole = new Hole ((Map::MAP_WIDTH - Ball::BALL_HEIGHT) * 0.5f, 100.0f);

Obstacle* obstacle1 = new Obstacle("Rectangle", 450.0f, 300.0f, 200.0f, 100.0f);
Obstacle* obstacle2 = new Obstacle("Triangle", 400.0f, 100.0f, 300.0f, 100.0f);
Obstacle* obstacle3 = new Obstacle("Triangle", 50.0f, 500.0f, 100.0f, 100.0f);

std::vector<Obstacle*> obstacles = { obstacle1, obstacle2, obstacle3 };

Portal* EntryPortal, * ExitPortal;

Ball* ball;

Button* playButton, *replayButton, *nextLevelButton;

PowerBar* powerBar;

Shots* shots;

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
SDL_FRect Game::camera = { 0.0f , 0.0f , Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT };

Mix_Chunk* Game::chunkHit = nullptr;
Mix_Chunk* Game::chunkDrop = nullptr;
Mix_Chunk* Game::chunkCollide = nullptr;

enum GameState { Menu, Playing, Pause, GameOver };
GameState currentState = Menu;

std::vector < const char* > WinStates = { "assets/WinState0Stars.png", "assets/WinState1Stars.png", "assets/WinState2Stars.png", "assets/WinState3Stars.png" };

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

	map->LoadMap("assets/TileMap2.txt", 50, 40);

	MenuBg = new Background("assets/MenuBg.png", 0.0f, 0.0f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
	WinStateBg = new Background(WinStates[3], (Game::WINDOW_WIDTH - 400) * 0.5f, (Game::WINDOW_HEIGHT - 400) * 0.5f, 400.0f, 400.0f);

	MenuBg->init();
	WinStateBg->init();

	for (auto& obstacle : obstacles) obstacle->init();

	EntryPortal = new Portal("assets/EntryPortal.png",800, 600, 80, 80);
	ExitPortal = new Portal("assets/ExitPortal.png", 500, 600, 80, 80);

	ball = new Ball(Map::MAP_WIDTH / 2 - Ball::BALL_WIDTH / 2, Map::MAP_HEIGHT / 2 - Ball::BALL_HEIGHT / 2);
	ball->init();

	hole->init();

	powerBar = new PowerBar();
	powerBar->init();

	playButton = new Button("assets/buttonPlay.png", (Game::WINDOW_WIDTH - 150) * 0.5f, (Game::WINDOW_HEIGHT - 150) * 0.5f + 50.0f, 150.0f, 80.0f);
	replayButton = new Button("assets/ReplayButton.png", (Game::WINDOW_WIDTH - 80) * 0.5f, (Game::WINDOW_HEIGHT - 20) * 0.5f, 80.0f, 80.0f);

	playButton->init();
	replayButton->init();

	shots = new Shots();
}

void Game::handleEvents()
{
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT) isRunning = false;

		else if (currentState == Menu)
		{
			playButton->handleEvent(event);
			if (playButton->isPressed()) currentState = Playing;
		}

		else if (currentState == Playing)
		{	
			ball->handleEvent(event);

		}

		else if (currentState == GameOver)
		{
			replayButton->handleEvent(event);
			if (replayButton->isPressed())
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
		MenuBg->update();
		playButton->update();
	}

	else if (currentState == Playing)
	{
		hole->update();

		for (auto& obstacle : obstacles) obstacle->update();

		ball->update();
		
		powerBar->update();

		shots->update();

		EntryPortal->update();
		ExitPortal->update();

		if ( std::fabs(ball->position.x - hole->position.x) <= 5.0f &&
			std::fabs(ball->position.y - hole->position.y) <= 5.0f)
		{
			Mix_PlayChannel(-1, chunkDrop, 0);

			std::cout << "Congratulation!! " << remainingShots << std::endl;

			currentState = GameOver;
			WinStateBg->changeTexture(WinStates[remainingShots+1]);
		}
		else if (remainingShots == 0 && ball->stop())
		{
			std::cout << "You reached the shot limit! " << remainingShots << std::endl;
			currentState = GameOver;
			WinStateBg->changeTexture(WinStates[remainingShots]);
		}
	}

	else if (currentState == GameOver)
	{
		WinStateBg->update();
		replayButton->update();
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);
	
	if (currentState == Menu)
	{
		MenuBg->render();
		playButton->render();
	}

	else if (currentState == Playing)
	{
		for (auto& tile : map->tiles) tile->render();

		hole->render();

		for (auto& obstacle : obstacles) obstacle->render();

		EntryPortal->render();
		ExitPortal->render();

		ball->render();
		powerBar->render();
		shots->render();

	}

	else if (currentState == GameOver)
	{
		for (auto& tile : map->tiles) tile->render();

		hole->render();

		for (auto& obstacle : obstacles) obstacle->render();

		EntryPortal->render();
		ExitPortal->render();

		powerBar->render();
		shots->render();

		EntryPortal->render();
		ExitPortal->render();

		WinStateBg->render();
		replayButton->render();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	delete MenuBg;
	delete WinStateBg;
	delete ball;
	delete hole;
	delete playButton;
	delete replayButton;
	delete powerBar;
	delete shots;
	delete EntryPortal;
	delete ExitPortal;

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
