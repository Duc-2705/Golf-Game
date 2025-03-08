#pragma once

#include "Vector2D.h"

class Cursor
{
private:
	int xMouseDown = 0, yMouseDown = 0;
	int xMouseUp = 0, yMouseUp = 0;

	Vector2D force;

	bool checkPulling = false;

public:
	Cursor();
	~Cursor() {}

	void handleEvents();

	bool isPulling() { return checkPulling; }

	Vector2D Force();
};