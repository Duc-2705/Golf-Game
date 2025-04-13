#pragma once

#include "Vector2D.h"
#include "Game.h"
#include "TextureManager..h"

class Button
{
private:
	SDL_Texture* texButton = nullptr;
	SDL_Texture* texText = nullptr;

	SDL_Rect srcButton;
	SDL_FRect destButton;
	SDL_FRect destText;

	bool mouseDown = false;
	bool pressed = false;

	float scale = 1.0f;

public:
	float BUTTON_WIDTH;
	float BUTTON_HEIGHT;

	Vector2D position;

	Button(const float& xPos, const float& yPos, const float& w, const float& h);
	Button(const char* text, const float& xPos, const float& yPos, const float& w, const float& h);

	~Button();

	bool isPressed() { return pressed; }

	void init();
	void handleEvent(SDL_Event& event);
	void update();
	void render();
};