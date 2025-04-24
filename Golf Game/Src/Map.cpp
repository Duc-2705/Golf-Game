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

void Map::LoadMap(const char* path,const int& sizeX, const int& sizeY)
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
				int srcY = (c - '0') * Tile::TILE_HEIGHT;

				mapFile >> c;
				int srcX = (c - '0') * Tile::TILE_WIDTH;

				Tile* tile = new Tile(srcX, srcY, x * Tile::TILE_WIDTH, y * Tile::TILE_HEIGHT);

				tile->init();

				if (srcX == 0 && srcY == 0) waterTiles.push_back(tile);
				else if (srcY == 32 || ( srcY == 0 && srcX >= 32*3)) sandTiles.push_back(tile);
				
				tiles.push_back(tile);

				mapFile.ignore();
			}
		}
		mapFile.close();
	}
}