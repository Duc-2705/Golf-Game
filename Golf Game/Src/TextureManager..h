#pragma once
#include "Game.h"

class TextureManager
{
public:
	static SDL_Texture* LoadTexture(const char* path);

	static SDL_Texture* LoadTextureText(const char* text, SDL_Color color);

	static void setSrcRect(SDL_Texture* texture, SDL_Rect& src);

	static void Draw(SDL_Texture* texture, SDL_Rect& src, SDL_FRect& dest);

};