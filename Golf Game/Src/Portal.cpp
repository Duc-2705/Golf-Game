#include "Portal.h"

Portal::Portal(const char* path, const float& x, const float& y, const float& w, const float& h)
{
	texPortal = TextureManager::LoadTexture(path);
	TextureManager::setSrcRect(texPortal, srcPortal);
	srcPortal.w /= column;
	srcPortal.h /= row;

	destPortal = { x,y,w,h };

	PORTAL_WIDTH = w;
	PORTAL_HEIGHT = h;
	
	position.x = x;
	position.y = y;
}

Portal::~Portal()
{
	SDL_DestroyTexture(texPortal);
}

void Portal::init()
{


}

void Portal::update()
{
	srcPortal.x = srcPortal.w * ((static_cast<int>(SDL_GetTicks() / speed) % frames) % column);
	srcPortal.y = srcPortal.h * ((static_cast<int>(SDL_GetTicks() / speed) % frames) % row);
}

void Portal::render()
{
	TextureManager::Draw(texPortal, srcPortal, destPortal);
}