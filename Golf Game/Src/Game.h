#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <iostream>
#include "Obstacle.h"
#include <vector>

class Game
{
private:
	bool isRunning = false;
	
	SDL_Window* window;

public:
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 640;

	static Mix_Chunk* chunkHit;
	static Mix_Chunk* chunkDrop;
	static Mix_Chunk* chunkCollide;
	static Mix_Chunk* chunkWaterDrop;

	static SDL_Event event;
	static SDL_Renderer* renderer;

	static TTF_Font* font;

	static SDL_FRect camera;

	static int remainingShots;

	static int currentLevel;

	Game();
	~Game();

	void init(const char* tilte, bool fullscreen);

	void handleEvents();

	bool running() { return isRunning; }

	void update();

	void render();

	void clean();
};