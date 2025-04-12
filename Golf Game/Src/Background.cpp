#include "Background.h"

Background::Background(const char* path, const float& xPos, const float& yPos, const float& w, const float& h)
{
	texBg = TextureManager::LoadTexture(path);
	
	destBg = { xPos, yPos, w, h };
}

Background::~Background()
{
	SDL_DestroyTexture(texBg);
}

void Background::init()
{
	TextureManager::setSrcRect(texBg, srcBg);
}

void Background::update()
{

}

void Background::render()
{
	SDL_RenderCopyF(Game::renderer, texBg, &srcBg, &destBg);
}