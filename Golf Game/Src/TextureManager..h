#pragma once
#include "Game.h"

class TextureManager
{
private:
public:
	static SDL_Texture* LoadTexture(const char* path);

	static void setSrcRect(SDL_Texture* texture, SDL_Rect& src);

	static void Draw(SDL_Texture* texture, SDL_Rect src, SDL_FRect dest);

};