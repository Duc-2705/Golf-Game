#include "Cursor.h"
#include "Game.h"
#include "Utilities.h"
#include "Map.h"

extern Map* map;

Cursor::Cursor()
{
	arrow = new Arrow();
	arrow->init();
}

Cursor::~Cursor()
{
	delete arrow;
	arrow = nullptr;
}

void Cursor::handleEvent(SDL_Event& event)
{
	switch (event.type)
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

		arrow->setAngle(atan2(yMouseState - yMouseDown, xMouseState - xMouseDown) * 180 / M_PI + 180); //Goc quay
		arrow->update();

		magForce = std::min (maxMagForce, Vector2D::getMagnitude(static_cast<float>(xMouseState - xMouseDown), static_cast<float>(yMouseState - yMouseDown)));

		arrow->setRange(magForce); //Do lon mui ten

		this->updateCamera();
	}
	else
	{
		magForce = 0.0f;
	}
}

void Cursor::updateCamera()
{
	Vector2D v(xMouseDown - xMouseState, yMouseDown - yMouseState);

	float radius = std::min(100.0f, v.magnitude);
	float targetCenterX = map->ball->center.x + v.i * radius;
	float targetCenterY = map->ball->center.y + v.j * radius;

	Game::camera.x = lerp(Game::camera.x, targetCenterX - Game::camera.w / 2, 0.1f);
	Game::camera.x = std::max(0.0f, std::min(Game::camera.x, Map::MAP_WIDTH - Game::camera.w));

	Game::camera.y = lerp(Game::camera.y, targetCenterY - Game::camera.h / 2, 0.1f);
	Game::camera.y = std::max(0.0f, std::min(Game::camera.y, Map::MAP_HEIGHT - Game::camera.h));
}

Vector2D Cursor::Force()
{
	checkPulling = false;
	Vector2D force(xMouseUp - xMouseDown, yMouseUp - yMouseDown);
	force.magnitude = std::min(maxMagForce, force.magnitude);
	return force;
}

float Cursor::getPercentageMagForce()
{
	return magForce / maxMagForce;
}