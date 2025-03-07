#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game
{
private:
	bool isRunning = false;
	
	SDL_Window* window;
	SDL_Event event;
	SDL_Rect srcRect, destRect;
public:
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