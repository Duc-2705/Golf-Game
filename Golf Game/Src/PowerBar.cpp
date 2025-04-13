#include "PowerBar.h"
#include "Utilities.h"

PowerBar::PowerBar(Cursor* cursor)
{
	this->cursor = cursor;

	texBar = TextureManager::LoadTexture("assets/powerBar.png");
	TextureManager::setSrcRect(texBar, srcBar);

	texMaxBar = TextureManager::LoadTexture("assets/maxPowerBar.png");
	TextureManager::setSrcRect(texMaxBar, srcMaxBar);

	power = 0.0f;
}

PowerBar::~PowerBar()
{
	SDL_DestroyTexture(texBar);
	SDL_DestroyTexture(texMaxBar);
}

void PowerBar::init()
{
	destMaxBar.x = destBar.x = Game::WINDOW_WIDTH - 100.0f;
	destBar.y = 200.0f;
	destMaxBar.w = destBar.w = 50.0f;
	destBar.h = 300.0f;

}

void PowerBar::update()
{
	power = cursor->getPercentageMagForce();

	srcMaxBar.h = srcBar.h * power;
	srcMaxBar.y = srcBar.y + srcBar.h - srcBar.h * power;

	destMaxBar.h = destBar.h * power;
	destMaxBar.y = destBar.y + destBar.h - destBar.h * power;
}

void PowerBar::render()
{
	SDL_RenderCopyF(Game::renderer, texBar, &srcBar, &destBar);
	SDL_RenderCopyF(Game::renderer, texMaxBar, &srcMaxBar, &destMaxBar);
}
