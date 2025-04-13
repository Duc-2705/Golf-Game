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

	if (texText)
	{
		texButton = TextureManager::LoadTexture("assets/Button.png");
		TextureManager::setSrcRect(texButton, srcButton);

		destText.x = destButton.x + 4;
		destText.y = destButton.y + 4;
		destText.w = destButton.w - 10;
		destText.h = destButton.h - 10;
	}

	else
	{
		texButton = TextureManager::LoadTexture("assets/buttonPlay.png");
		TextureManager::setSrcRect(texButton, srcButton);
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
			yMouse >= position.y && yMouse <= position.y + BUTTON_HEIGHT)
		{
			mouseDown = true;
		}
		break;

	case SDL_MOUSEBUTTONUP:
		if (mouseDown)
		{
			pressed = true;
			mouseDown = false;

		}
		break;
	}
}

void Button::update()
{
	scale = (mouseDown) ? 0.8f : 1.0f;

	destButton.w = BUTTON_WIDTH * scale;
	destButton.h = BUTTON_HEIGHT * scale;

	destButton.x = position.x + (BUTTON_WIDTH - destButton.w) / 2;
	destButton.y = position.y + (BUTTON_HEIGHT - destButton.h) / 2;

}

void Button::render()
{
	SDL_RenderCopyF(Game::renderer, texButton, &srcButton, &destButton);

	if (texText) SDL_RenderCopyF(Game::renderer, texText, nullptr, &destText);
}