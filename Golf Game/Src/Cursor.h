#pragma once

#include "Vector2D.h"

class Cursor
{
private:
	int xMouseDown, yMouseDown;
	int xMouseUp, yMouseUp;

	bool checkPulling = false;

public:
	Cursor();
	~Cursor() {}

	void handleEvents();

	bool isPulling() { return checkPulling; }

	Vector2D Force();
};