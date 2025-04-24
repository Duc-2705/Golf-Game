#include "Tile.h"
#include "TextureManager..h"

Tile::Tile(const int& srcX, const int& srcY, const int& xPos, const int& yPos)
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
	texTile = TextureManager::LoadTexture("assets/TileSet5.png");
}

void Tile::render()
{
	TextureManager::Draw(texTile, srcTile, destTile);
}