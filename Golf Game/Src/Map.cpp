#include "Map.h"
#include <fstream>

Map::Map() {}

Map::~Map()
{
	for (auto& tile : tiles)
	{
		delete tile;
		tile = nullptr;
	}
}

void Map::LoadMap(const char* path, int sizeX, int sizeY)
{
	char c;
	std::ifstream mapFile;
	mapFile.open(path);
	if (mapFile.is_open())
	{
		for (int y = 0; y < sizeY; y++)
		{
			for (int x = 0; x < sizeX; x++)
			{
				mapFile >> c;

				int srcX = (c - '0') * Tile::TILE_WIDTH;

				Tile* tile = new Tile(srcX, 0, x * Tile::TILE_WIDTH, y * Tile::TILE_HEIGHT);
				tile->init();
				
				tiles.push_back(tile);

				mapFile.ignore();
			}
		}
		mapFile.close();
	}
}