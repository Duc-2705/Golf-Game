#include "Cursor.h"
#include "Game.h"
#include "Utilities.h"
#include "Map.h"

Cursor::Cursor(Ball* ball)
{
	this->ball = ball;
	arrow = new Arrow(ball);
	arrow->init();
}

Cursor::~Cursor()
{
	delete arrow;
	arrow = nullptr;
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
		if (MouseDown)
		{
			SDL_GetMouseState(&xMouseUp, &yMouseUp);
			checkPulling = true;
			MouseDown = false;
		}
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

		float mag = Vector2D::getMagnitude(static_cast<float>(xMouseState - xMouseDown), static_cast<float>(yMouseState - yMouseDown));

		arrow->setRange(mag); //Do lon mui ten
		arrow->render();

		this->updateCamera();
	}
}

void Cursor::updateCamera()
{
	Vector2D v(xMouseDown - xMouseState, yMouseDown - yMouseState);

	float radius = std::min(100.0f, v.magnitude);
	float targetCenterX = ball->center.x + v.i * radius;
	float targetCenterY = ball->center.y + v.j * radius;

	Game::camera.x = lerp(Game::camera.x, targetCenterX - Game::camera.w / 2, 0.1f);
	Game::camera.x = std::max(0.0f, std::min(Game::camera.x, Map::MAP_WIDTH - Game::camera.w));

	Game::camera.y = lerp(Game::camera.y, targetCenterY - Game::camera.h / 2, 0.1f);
	Game::camera.y = std::max(0.0f, std::min(Game::camera.y, Map::MAP_HEIGHT - Game::camera.h));
}

Vector2D Cursor::Force()
{
	checkPulling = false;
	return Vector2D(xMouseUp - xMouseDown, yMouseUp - yMouseDown);
}