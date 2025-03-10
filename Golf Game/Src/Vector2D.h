#pragma once
#include <iostream>

class Vector2D
{
private:

public:
	float i, j; //vector don vi
	float x, y;
	float magnitude; // Do lon vector

	Vector2D() 
	{
		i = 0.0f;
		j = 0.0f;
		x = 0.0f; 
		y = 0.0f;
		magnitude = 0.0f;
	}

	Vector2D(int x, int y)
	{
		this->x = static_cast<float>(x);
		this->y = static_cast<float>(y);
		magnitude = Vector2D::getMagnitude(this->x, this->y);
	}

	Vector2D(float x, float y) : x(x), y(y) {};

	friend Vector2D operator+ (const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator- (const Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+= (const Vector2D& vec);
	Vector2D& operator-= (const Vector2D& vec);

	Vector2D operator* (const float& i);
	Vector2D operator/ (const float& i);

	Vector2D& operator= (const Vector2D& vec);

	void Zero();

	friend std::ostream& operator<< (std::ostream& stream, const Vector2D& vec);

	static float getMagnitude(float x, float y);
};