#include "Shots.h"

Shots::Shots()
{
	texShots = TextureManager::LoadTexture("assets/Shots.png");
	TextureManager::setSrcRect(texShots, srcShots);

	destShots.x = Game::WINDOW_WIDTH - 100.0f;
	destShots.y = 10.0f;
	destShots.w = 32.0f * 3;
	destShots.h = 32.0f;
}

Shots::~Shots()
{
	SDL_DestroyTexture(texShots);
}

void Shots::update()
{
	srcShots.w = 64 * Game::remainingShots;

	destShots.w = 32.0f * Game::remainingShots;
}

void Shots::render()
{
	SDL_RenderCopyF(Game::renderer, texShots, &srcShots, &destShots);
}