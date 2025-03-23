#pragma once

#include "Tile.h"
#include <vector>

class Map
{
public:
	std::vector<Tile*> tiles;
	
	Map();
	~Map();

	void LoadMap(const char* path, int sizeX, int sizeY);
};