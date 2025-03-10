#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>



class Game
{
private:
	bool isRunning = false;
	bool win = false;
	
	SDL_Window* window;
public:
	static const int WINDOW_WIDTH = 800;
	static const int WINDOW_HEIGHT = 640;

	static SDL_Event event;
	static SDL_Renderer* renderer;

	Game();
	~Game();

	void init(const char* tilte, int width, int height, bool fullscreen);

	void handleEvents();

	bool running() { return isRunning; }

	void update();

	void render();

	void clean();
};