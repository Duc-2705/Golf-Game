#include "Tile.h"
#include "TextureManager..h"

Tile::Tile(int srcX, int srcY, int xPos, int yPos)
{
	srcTile.x = srcX;
	srcTile.y = srcY;
	srcTile.w = TILE_WIDTH;
	srcTile.h = TILE_HEIGHT;

	destTile.x = static_cast<float>(xPos);
	destTile.y = static_cast<float>(yPos);
	destTile.w = static_cast<float>(TILE_WIDTH);
	destTile.h = static_cast<float>(TILE_HEIGHT);
}

Tile::~Tile()
{
	SDL_DestroyTexture(texTile);
}

void Tile::init()
{
	texTile = TextureManager::LoadTexture("assets/TileSet1.png");
}

void Tile::render()
{
	TextureManager::Draw(texTile, srcTile, destTile);
}