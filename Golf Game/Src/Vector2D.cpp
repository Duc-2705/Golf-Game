#include "Vector2D.h"

Vector2D operator+ (const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D (v1.x + v2.x, v1.y + v2.y);
}

Vector2D operator- (const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D (v1.x - v2.x, v1.y - v2.y);
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}

Vector2D Vector2D::operator*(const float& i)
{
	return Vector2D(this->x * i, this->y * i);
}

Vector2D Vector2D::operator/ (const float& i)
{
	return Vector2D(this->x / i, this->y / i);
}

Vector2D& Vector2D::operator= (const Vector2D& vec)
{
	this->x = vec.x;
	this->y = vec.y;
	return *this;
}

Vector2D& Vector2D::Zero()
{
	this->x = 0.0f;
	this->y = 0.0f;
	return *this;
}

std::ostream& operator<< (std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << " , " << vec.y << ")";
	return stream;
}

