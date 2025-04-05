#pragma once

#include "Tile.h"
#include <vector>

class Map
{
public:
	static const int MAP_WIDTH = 1600;
	static const int MAP_HEIGHT = 1280;

	std::vector<Tile*> tiles;
	
	Map();
	~Map();

	void LoadMap(const char* path,const int& sizeX,const int& sizeY);
};