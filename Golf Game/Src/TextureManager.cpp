#include "TextureManager..h"

SDL_Texture* TextureManager::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load(path);

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255)); // xoa nen trang

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void TextureManager::setSrcRect(SDL_Texture* texture, SDL_Rect& src)
{
	src.x = src.y = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &(src.w), &(src.h)); //Lay kich thuoc anh goc
}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect& src, SDL_FRect& dest)
{
	SDL_FRect renderRect = { dest.x - Game::camera.x, dest.y - Game::camera.y, dest.w, dest.h };
	SDL_RenderCopyF(Game::renderer, texture, &src, &renderRect);
}
