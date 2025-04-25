#pragma once

#include "Game.h"
#include "Ball.h"
#include "Hole.h"
#include "Tile.h"
#include <vector>

class Map
{
private:
	const int sizeX = 40;
	const int sizeY = 30;

public:
	static const int MAP_WIDTH = 1280;
	static const int MAP_HEIGHT = 960;

	std::vector<Tile*> tiles;
	std::vector<Tile*> sandTiles;
	std::vector<Tile*> waterTiles;

	Ball* ball = nullptr;
	Hole* hole = nullptr;

	Portal* EntryPortal = nullptr, * ExitPortal = nullptr;
	
	std::vector<Obstacle*> obstacles;
	
	Map();
	~Map();

	void loadMapLvl(const int& level);
	void loadTileMap(const int& level);
	void clear();
};