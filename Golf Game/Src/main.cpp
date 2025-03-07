#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();

	game->init("Golf game", 800, 640, false);
	game->render();
	SDL_Delay(3000);
	game->handleEvents();
	game->clean();

	delete game;

	return 0;
}