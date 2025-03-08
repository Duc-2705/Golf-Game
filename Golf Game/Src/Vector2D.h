#pragma once
#include <iostream>

class Vector2D
{
public:
	float x, y;

	Vector2D() 
	{
		x = 0.0f; 
		y = 0.0f;
	}

	Vector2D(int x, int y)
	{
		this->x = static_cast<float>(x);
		this->y = static_cast<float>(y);
	}

	Vector2D(float x, float y) : x(x), y(y) {};

	friend Vector2D operator+ (const Vector2D& v1, const Vector2D& v2);
	friend Vector2D operator- (const Vector2D& v1, const Vector2D& v2);

	Vector2D& operator+= (const Vector2D& vec);
	Vector2D& operator-= (const Vector2D& vec);

	Vector2D operator* (const float& i);
	Vector2D operator/ (const float& i);

	Vector2D& operator= (const Vector2D& vec);

	Vector2D& Zero();

	friend std::ostream& operator<< (std::ostream& stream, const Vector2D& vec);
};