#include "TextureManager..h"

SDL_Texture* TextureManager::LoadTexture(const char* path)
{
	SDL_Surface* surface = IMG_Load("assets/ball.png");

	SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 255, 255, 255)); // xoa nen trang

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}
void TextureManager::setSrcRect(SDL_Texture* texture, SDL_Rect& src)
{
	src.x = src.y = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &(src.w), &(src.h));

}

void TextureManager::Draw(SDL_Texture* texture, SDL_Rect src, SDL_Rect dest)
{
	SDL_RenderCopy(Game::renderer, texture, &src, &dest);
}
