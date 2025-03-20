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

	bool checkPulling = false;
	bool MouseDown = false;

public:
	Cursor(Ball* ball);
	~Cursor();

	void handleEvents();

	void update();

	bool isPulling() { return checkPulling; }

	Vector2D Force();

	void clean();
};