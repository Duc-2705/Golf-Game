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

Button* playButton, * replayButton, * nextLevelButton, * levelButton;
Button* lvl1Button, * lvl2Button, * lvl3Button;

PowerBar* powerBar;

Shots* shots;

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
SDL_FRect Game::camera = { (Map::MAP_WIDTH - Game::WINDOW_WIDTH) * 0.5f , (Map::MAP_HEIGHT - Game::WINDOW_HEIGHT) * 0.5f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT };

Mix_Chunk* Game::chunkHit = nullptr;
Mix_Chunk* Game::chunkDrop = nullptr;
Mix_Chunk* Game::chunkCollide = nullptr;
Mix_Chunk* Game::chunkWaterDrop = nullptr;

enum GameState { Menu, Playing, Level, Pause, GameOver };
GameState currentState = Menu;

std::vector < const char* > WinStates = { "assets/WinState0Stars.png", "assets/WinState1Stars.png", "assets/WinState2Stars.png", "assets/WinState3Stars.png" };

std::vector < const char* > MapFiles = { "assets/MapLevel1.txt", "assets/MapLevel2.txt", "assets/MapLevel3.txt"};
int Game::currentLevel = 0;

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
			SDL_SetRenderDrawColor(renderer, 255, 224, 189, 255);
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
	chunkWaterDrop = Mix_LoadWAV("sound/water_drop.wav");

	font = TTF_OpenFont("font/arial.ttf", 24);

	map->loadMapLvl(currentLevel);

	MenuBg = new Background("assets/MenuBg.png", 0.0f, 0.0f, Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT);
	WinStateBg = new Background(WinStates[3], (Game::WINDOW_WIDTH - 400) * 0.5f, (Game::WINDOW_HEIGHT - 400) * 0.5f, 400.0f, 400.0f);

	MenuBg->init();
	WinStateBg->init();

	powerBar = new PowerBar();
	powerBar->init();

	playButton = new Button("assets/buttonPlay.png", (Game::WINDOW_WIDTH - 150) * 0.5f, (Game::WINDOW_HEIGHT - 150) * 0.5f + 50.0f, 150.0f, 80.0f);
	replayButton = new Button("assets/ReplayButton.png", (Game::WINDOW_WIDTH - 80) * 0.5f, (Game::WINDOW_HEIGHT - 20) * 0.5f, 80.0f, 80.0f);
	nextLevelButton = new Button("assets/PlayButton.png", (Game::WINDOW_WIDTH - 80) * 0.5f + 80.0f, (Game::WINDOW_HEIGHT - 20) * 0.5f, 80.0f, 80.0f);
	levelButton = new Button("assets/LevelButton.png", (Game::WINDOW_WIDTH - 80) * 0.5f - 80.0f, (Game::WINDOW_HEIGHT - 20) * 0.5f, 80.0f, 80.0f);

	lvl1Button= new Button("assets/Level1.png", (Game::WINDOW_WIDTH - 100) * 0.5f - 100.0f, (Game::WINDOW_HEIGHT - 100) * 0.5f, 100.0f, 100.0f);
	lvl2Button = new Button("assets/Level2.png", (Game::WINDOW_WIDTH - 100) * 0.5f , (Game::WINDOW_HEIGHT - 100) * 0.5f, 100.0f, 100.0f);
	lvl3Button = new Button("assets/Level3.png", (Game::WINDOW_WIDTH - 100) * 0.5f + 100.0f, (Game::WINDOW_HEIGHT - 100) * 0.5f, 100.0f, 100.0f);

	playButton->init();
	replayButton->init();
	nextLevelButton->init();
	levelButton->init();

	lvl1Button->init();
	lvl2Button->init();
	lvl3Button->init();

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
			if (playButton->isPressed()) currentState = Level;
		}

		else if (currentState == Playing)
		{
			map->ball->handleEvent(event);

		}

		else if (currentState == Level)
		{
			lvl1Button->handleEvent(event);
			if (lvl1Button->isPressed())
			{
				currentState = Playing;
				currentLevel = 0;
				remainingShots = 3;

				map->loadMapLvl(currentLevel);
			}

			lvl2Button->handleEvent(event);
			if (lvl2Button->isPressed())
			{
				currentState = Playing;
				currentLevel = 1;
				remainingShots = 3;

				map->loadMapLvl(currentLevel);
			}

			lvl3Button->handleEvent(event);
			if (lvl3Button->isPressed())
			{
				currentState = Playing;
				currentLevel = 2;
				remainingShots = 3;

				map->loadMapLvl(currentLevel);
			}
		}

		else if (currentState == GameOver)
		{
			replayButton->handleEvent(event);
			if (replayButton->isPressed())
			{
				currentState = Playing;
				map->ball->reset();
			}

			nextLevelButton->handleEvent(event);
			if (nextLevelButton->isPressed())
			{
				currentState = Playing;

				remainingShots = 3;
				currentLevel++;
				map->loadMapLvl(currentLevel % MapFiles.size());
			}

			levelButton->handleEvent(event);
			if (levelButton->isPressed())
			{
				currentState = Level;
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
		map->hole->update();

		for (auto& obstacle : map->obstacles) obstacle->update();

		map->ball->update();
		
		powerBar->update();

		shots->update();

		map->EntryPortal->update();
		map->ExitPortal->update();

		if (map->ball->checkWaterDrop())
		{
			Mix_PlayChannel(-1, chunkWaterDrop, 0);

			std::cout << "Water Drop! " << remainingShots << std::endl;

			currentState = GameOver;
			WinStateBg->changeTexture(WinStates[0]);
		}
		else if ( std::fabs(map->ball->position.x - map->hole->position.x) <= 5.0f &&
			std::fabs(map->ball->position.y - map->hole->position.y) <= 5.0f)
		{
			Mix_PlayChannel(-1, chunkDrop, 0);

			std::cout << "Congratulation!! " << remainingShots << std::endl;

			currentState = GameOver;
			WinStateBg->changeTexture(WinStates[remainingShots+1]);
		}
		else if (remainingShots == 0 && map->ball->stop())
		{
			std::cout << "You reached the shot limit! " << remainingShots << std::endl;
			currentState = GameOver;
			WinStateBg->changeTexture(WinStates[remainingShots]);
		}
	}

	else if (currentState == Level)
	{
		lvl1Button->update();
		lvl2Button->update();
		lvl3Button->update();
	}

	else if (currentState == GameOver)
	{
		WinStateBg->update();
		replayButton->update();
		nextLevelButton->update();
		levelButton->update();
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

		map->hole->render();

		for (auto& obstacle : map->obstacles) obstacle->render();

		map->EntryPortal->render();
		map->ExitPortal->render();

		map->ball->render();
		powerBar->render();
		shots->render();

	}

	else if (currentState == Level)
	{
		lvl1Button->render();
		lvl2Button->render();
		lvl3Button->render();
	}

	else if (currentState == GameOver)
	{
		for (auto& tile : map->tiles) tile->render();

		map->hole->render();

		for (auto& obstacle : map->obstacles) obstacle->render();

		map->EntryPortal->render();
		map->ExitPortal->render();

		powerBar->render();
		shots->render();

		map->EntryPortal->render();
		map->ExitPortal->render();

		WinStateBg->render();
		replayButton->render();
		nextLevelButton->render();
		levelButton->render();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	delete map;
	delete MenuBg;
	delete WinStateBg;
	delete playButton;
	delete replayButton;
	delete nextLevelButton;
	delete levelButton;
	delete lvl1Button;
	delete lvl2Button;
	delete lvl3Button;
	delete powerBar;
	delete shots;

	Mix_FreeChunk(chunkHit);
	Mix_FreeChunk(chunkDrop);
	Mix_FreeChunk(chunkCollide);
	Mix_FreeChunk(chunkWaterDrop);

	TTF_CloseFont(font);

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}
