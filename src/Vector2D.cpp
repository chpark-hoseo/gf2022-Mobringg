#include "Vector2D.h"

//4칙연산
Vector2D Vector2D::operator+(const Vector2D& v2) const
{
	return Vector2D(m_x + v2.m_x, m_y + v2.m_y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const
{
	return Vector2D(m_x - v2.m_x, m_y - v2.m_y);
}

Vector2D Vector2D::operator*(float scalar)
{
	return Vector2D(m_x * scalar, m_y * scalar);
}

Vector2D Vector2D::operator/(float scalar)
{
	return Vector2D(m_x / scalar, m_y / scalar);
}

//축약 연산
Vector2D& Vector2D::operator*=(float scalar)
{
	m_x *= scalar;
	m_y *= scalar;
	return *this;
}

Vector2D& Vector2D::operator/=(float scalar)
{
	m_x /= scalar;
	m_y /= scalar;
	return *this;
}

//벡터 정규화
void Vector2D::normalize()
{
	float l = length();
	if (l > 0) // we never want to attempt to divide by 0
	{
		(*this) *= 1 / l;
	}
}

//friend 함수
Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
{
	v1.m_x += v2.m_x;
	v1.m_y += v2.m_y;
	return v1;
}

Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
{
	v1.m_x -= v2.m_x;
	v1.m_y -= v2.m_y;
	return v1;
}