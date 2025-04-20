#pragma once

#include "Arrow.h"
#include "Ball.h"
#include "Vector2D.h"
#include "Game.h"

class Arrow;

class Cursor
{
private:
	int xMouseDown, yMouseDown;
	int xMouseUp, yMouseUp;
	int xMouseState, yMouseState;

	bool checkPulling = false;

	const float maxMagForce = 600.0f;

	void updateCamera();

public:
	Arrow* arrow;
	float magForce = 0.0f;

	bool MouseDown = false;

	Cursor();
	~Cursor();

	void handleEvent(SDL_Event& event);
	void update();
	bool Pulled() { return checkPulling; }

	float getPercentageMagForce();

	Vector2D Force();
};