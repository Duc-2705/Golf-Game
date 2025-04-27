#include "HoleMarker.h"
#include "Map.h"
#include "Collision.h"

extern Map* map;

HoleMarker::HoleMarker()
{

}

HoleMarker::~HoleMarker()
{

}


bool HoleMarker::checkHoleInCamera()
{
	Hole* hole = map->hole;

	return hole->position.x + hole->HOLE_WIDTH > Game::camera.x && hole->position.x < Game::camera.x + Game::camera.w &&
		hole->position.y + hole->HOLE_HEGHT > Game::camera.y && hole->position.y < Game::camera.y + Game::camera.h;
}

void HoleMarker::update()
{
	if (!checkHoleInCamera())
	{
		markerPos.x = std::max(Game::camera.x, std::min(Game::camera.x + Game::camera.w - 20, map->hole->position.x));
		markerPos.y = std::max(Game::camera.y, std::min(Game::camera.y + Game::camera.h - 20, map->hole->position.y));
	}
}

void HoleMarker::render()
{
	if (!checkHoleInCamera())
	{
		SDL_SetRenderDrawColor(Game::renderer, 255, 0, 0, 255);

		SDL_FRect marker = { markerPos.x - Game::camera.x, markerPos.y - Game::camera.y, 20, 20 };

		SDL_RenderFillRectF(Game::renderer, &marker);

		SDL_SetRenderDrawColor(Game::renderer, 255, 224, 189, 255);
	}
}