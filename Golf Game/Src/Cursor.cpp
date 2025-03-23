#include "Cursor.h"
#include "Game.h"

Cursor::Cursor(Ball* ball)
{
	arrow = new Arrow(ball);
	arrow->init();
}

Cursor::~Cursor()
{
}

void Cursor::handleEvents()
{
	switch (Game::event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		SDL_GetMouseState(&xMouseDown, &yMouseDown);
		MouseDown = true;
		break;

	case SDL_MOUSEBUTTONUP:
		SDL_GetMouseState(&xMouseUp, &yMouseUp);
		checkPulling = true; 
		MouseDown = false;
		break;

	default:
		break;
	}
}

void Cursor::update()
{
	if (MouseDown)
	{
		SDL_GetMouseState(&xMouseState, &yMouseState);
		arrow->setAngle(atan2(yMouseState - yMouseDown, xMouseState - xMouseDown) * 180/ M_PI + 180); //Goc quay
		arrow->update();

		float mag = static_cast<float>(sqrt((xMouseState - xMouseDown) * (xMouseState - xMouseDown) + (yMouseState - yMouseDown) * (yMouseState - yMouseDown)));

		arrow->setRange(mag); //Do lon mui ten

		arrow->render();
	}
}

void Cursor::clean()
{
	delete arrow;
	arrow = nullptr;
}

Vector2D Cursor::Force()
{
	checkPulling = false;
	return Vector2D(xMouseUp - xMouseDown, yMouseUp - yMouseDown);
}