#include "Game.h"
//#include <crtdbg.h> //thu vien check memory leak

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	
	game = new Game();

	game->init("Golf game", false);
	
	while (game->running())
	{
		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameTime < frameDelay)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	delete game;

	//_CrtDumpMemoryLeaks(); // Memory leak check

	return 0;
}