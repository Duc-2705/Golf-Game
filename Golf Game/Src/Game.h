#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
private:
	bool isRunning = false;
	
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event event;
public:
	Game();
	~Game();

	void init(const char* tilte, int width, int height, bool fullscreen);

	void handleEvents();

	bool running() { return isRunning; }

	void update();

	void render();

	void clean();
};