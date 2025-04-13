#include "Background.h"

Background::Background(const char* path, const float& xPos, const float& yPos, const float& w, const float& h)
{
	texBg = TextureManager::LoadTexture(path);
	TextureManager::setSrcRect(texBg, srcBg);
	
	destBg = { xPos, yPos, w, h };
}

Background::~Background()
{
	SDL_DestroyTexture(texBg);
}

void Background::init()
{

}

void Background::update()
{

}

void Background::render()
{
	SDL_RenderCopyF(Game::renderer, texBg, &srcBg, &destBg);
}

void Background::changeTexture(const char* path)
{
	if (texBg) SDL_DestroyTexture(texBg);
	texBg = TextureManager::LoadTexture(path);
	TextureManager::setSrcRect(texBg, srcBg);
}