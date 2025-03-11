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

void Vector2D::Zero()
{
	this->i = 0.0f;
	this->j = 0.0f;
	this->x = 0.0f;
	this->y = 0.0f;
	this->magnitude = 0.0f;
}

std::ostream& operator<< (std::ostream& stream, const Vector2D& vec)
{
	stream << "(" << vec.x << " , " << vec.y << ")";
	return stream;
}

float Vector2D::getMagnitude(float x, float y)
{
	return sqrt(x * x + y * y);
}

float Vector2D::DotProductUnit(const Vector2D& v1, const Vector2D& v2)
{
	return v1.i * v2.i + v1.j * v2.j;
}

float Vector2D::DotProduct(const Vector2D& v1, const Vector2D& v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}

float Vector2D::cosAngle(const Vector2D& v1, const Vector2D& v2)
{
	return Vector2D::DotProductUnit(v1, v2) / (Vector2D::getMagnitude(v1.i, v1.j) * Vector2D::getMagnitude(v2.i, v2.j));
}
