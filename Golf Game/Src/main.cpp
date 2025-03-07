#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	game = new Game();

	game->init("Golf game", 800, 640, false);
	
	while (game->running())
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	delete game;

	return 0;
}