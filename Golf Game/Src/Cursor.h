#pragma once

#include "Arrow.h"
#include "Ball.h"
#include "Vector2D.h"

class Ball;
class Arrow;

class Cursor
{
private:
	int xMouseDown, yMouseDown;
	int xMouseUp, yMouseUp;
	int xMouseState, yMouseState;

	Arrow* arrow;
	Ball* ball;

	bool checkPulling = false;

	void updateCamera();

public:
	bool MouseDown = false;

	Cursor(Ball* ball);
	~Cursor();

	void handleEvents();
	void update();
	bool Pulled() { return checkPulling; }

	Vector2D Force();
};