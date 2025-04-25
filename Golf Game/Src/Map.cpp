#include "Map.h"
#include <fstream>

extern std::vector < const char* > MapFiles;

Map::Map()
{
	
}

Map::~Map()
{
	clear();
}

void Map::loadMapLvl(const int& level)
{
	clear();

	loadTileMap(level);

	if (level == 0)
	{
		obstacles.emplace_back(new Obstacle("Rectangle", 450.0f, 300.0f, 200.0f, 100.0f));
		obstacles.emplace_back(new Obstacle("Triangle", 400.0f, 100.0f, 300.0f, 100.0f));
		obstacles.emplace_back(new Obstacle("Triangle", 50.0f, 500.0f, 100.0f, 100.0f));

		for (auto obstacle : obstacles) obstacle->init();

		ball = new Ball(Map::MAP_WIDTH / 2 - Ball::BALL_WIDTH / 2, 600.0f);
		ball->init();

		hole = new Hole(1000.0f, 100.0f);
		hole->init();

		EntryPortal = new Portal("assets/EntryPortal.png", 800, 600, 80, 80);
		ExitPortal = new Portal("assets/ExitPortal.png", 800, 200, 80, 80);
	}

	else if (level == 1)
	{
		obstacles.emplace_back(new Obstacle("Rectangle", 450.0f, 300.0f, 200.0f, 100.0f));
		obstacles.emplace_back(new Obstacle("Triangle", 400.0f, 100.0f, 300.0f, 100.0f));
		obstacles.emplace_back(new Obstacle("Triangle", 50.0f, 500.0f, 100.0f, 100.0f));

		for (auto obstacle : obstacles) obstacle->init();

		ball = new Ball(Map::MAP_WIDTH / 2 - Ball::BALL_WIDTH / 2, 600.0f);
		ball->init();

		hole = new Hole(1000.0f, 100.0f);
		hole->init();

		EntryPortal = new Portal("assets/EntryPortal.png", 800, 600, 80, 80);
		ExitPortal = new Portal("assets/ExitPortal.png", 800, 200, 80, 80);

	}
}

void Map::loadTileMap(const int& level)
{
	char c;
	std::ifstream mapFile;
	mapFile.open(MapFiles[level]);
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
				else if (srcY == 32 || (srcY == 0 && srcX >= 32 * 3)) sandTiles.push_back(tile);

				tiles.push_back(tile);

				mapFile.ignore();
			}
		}
		mapFile.close();
	}
}

void Map::clear()
{
	for (auto tile : tiles) delete tile;

	tiles.clear();
	sandTiles.clear();
	waterTiles.clear();

	if (ball) delete ball;
	if (hole) delete hole;

	for (auto obstacle : obstacles) delete obstacle;
	obstacles.clear();

	if (EntryPortal) delete EntryPortal;
	if (ExitPortal) delete ExitPortal;
}