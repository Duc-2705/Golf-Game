#include "Cursor.h"
#include "Game.h"

Cursor::Cursor(){}

void Cursor::handleEvents()
{
	switch (Game::event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&xMouseDown, &yMouseDown);
		break;
	case SDL_MOUSEBUTTONUP:
		SDL_GetMouseState(&xMouseUp, &yMouseUp);
		checkPulling = true;
		break;
	default:
		break;
	}
}

Vector2D Cursor::Force()
{
	checkPulling = false;
	return Vector2D(xMouseUp - xMouseDown, yMouseUp - yMouseDown);
}
