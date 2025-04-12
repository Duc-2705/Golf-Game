#include "Button.h"

Button::Button(const float& xPos, const float& yPos, const float& w, const float& h)
{
	destButton.x = xPos;
	destButton.y = yPos;
	destButton.w = w;
	destButton.h = h;

	position.x = xPos;
	position.y = yPos;

	BUTTON_WIDTH = w;
	BUTTON_HEIGHT = h;
}

Button::Button(const char* text, const float& xPos, const float& yPos, const float& w, const float& h)
{
	SDL_Color color = { 0, 0, 0 };
	texText = TextureManager::LoadTextureText(text, color);

	destButton.x = xPos;
	destButton.y = yPos;
	destButton.w = w;
	destButton.h = h;

	position.x = xPos;
	position.y = yPos;

	BUTTON_WIDTH = w;
	BUTTON_HEIGHT = h;
}

Button::~Button()
{
	SDL_DestroyTexture(texText);
	SDL_DestroyTexture(texButton);
}

void Button::init()
{
	texButton = TextureManager::LoadTexture("assets/Button.png");
	TextureManager::setSrcRect(texButton, srcButton);

	if (texText)
	{
		destText.x = destButton.x + 4;
		destText.y = destButton.y + 4;
		destText.w = destButton.w - 10;
		destText.h = destButton.h - 10;
	}
}

void Button::handleEvent(SDL_Event& event)
{
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		int xMouse, yMouse;
		SDL_GetMouseState(&xMouse, &yMouse);
		if (xMouse >= position.x && xMouse <= position.x + BUTTON_WIDTH &&
			yMouse >= position.y && yMouse <= position.y + BUTTON_HEIGHT) mouseDown = true;
		break;

	case SDL_MOUSEBUTTONUP:
		if (mouseDown)
		{
			pressed = true;
			mouseDown = false;
		}
	}
}

void Button::update()
{

}

void Button::render()
{
	SDL_RenderCopyF(Game::renderer, texButton, &srcButton, &destButton);

	if (texText) SDL_RenderCopyF(Game::renderer, texText, nullptr, &destText);
}