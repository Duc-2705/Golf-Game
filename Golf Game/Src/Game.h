#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>


const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 640;

class Game
{
private:
	bool isRunning = false;
	
	SDL_Window* window;
public:
	static SDL_Event event;
	static SDL_Renderer* renderer;
	static SDL_Texture* texture;

	Game();
	~Game();

	void init(const char* tilte, int width, int height, bool fullscreen);

	void handleEvents();

	bool running() { return isRunning; }

	void update();

	void render();

	void clean();
};