#pragma once

#include "Game.h"

class Tile
{
private:
	SDL_Texture* texTile;
	SDL_Rect srcTile;
	SDL_FRect destTile;

public:
	static const int TILE_WIDTH = 32;
	static const int TILE_HEIGHT = 32;

	Tile(int srcX, int srcY, int xPos, int yPos);
	~Tile();

	void init();
	void render();
};