#pragma once

#include "Tile.h"
#include <vector>

class Map
{
public:
	static const int MAP_WIDTH = 1280;
	static const int MAP_HEIGHT = 960;

	std::vector<Tile*> tiles;
	std::vector<Tile*> sandTiles;
	std::vector<Tile*> waterTiles;
	
	Map();
	~Map();

	void LoadMap(const char* path,const int& sizeX,const int& sizeY);
};