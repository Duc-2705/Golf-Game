#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include <iostream>
#include "Obstacle.h"
#include <vector>

class Obstacle;

class Game
{
private:
	bool isRunning = false;
	bool win = false;
	
	SDL_Window* window;

public:
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 640;

	static Mix_Chunk* chunkHit;
	static Mix_Chunk* chunkDrop;
	static Mix_Chunk* chunkCollide;

	static SDL_Event event;
	static SDL_Renderer* renderer;

	static SDL_FRect camera;

	static std::vector<Obstacle*> obstacles;

	Game();
	~Game();

	void init(const char* tilte, bool fullscreen);

	void handleEvents();

	bool running() { return isRunning; }

	void update();

	void render();

	void clean();
};