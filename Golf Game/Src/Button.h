#pragma once

#include "Vector2D.h"
#include "Game.h"
#include "TextureManager..h"

class Button
{
private:
	SDL_Texture* texButton = nullptr;

	SDL_Rect srcButton;
	SDL_FRect destButton;

	bool mouseDown = false;
	bool pressed = false;

	float scale = 1.0f;

public:
	float BUTTON_WIDTH;
	float BUTTON_HEIGHT;

	Vector2D position;

	Button(const char* path, const float& xPos, const float& yPos, const float& w, const float& h);

	~Button();

	bool isPressed();

	void init();
	void handleEvent(SDL_Event& event);
	void update();
	void render();
};