#ifndef _VEC2_HPP_
#define _VEC2_HPP_

struct Vector2
{
	Vector2();
	Vector2(float x, float y);

	Vector2 operator-();

	Vector2 operator+(const Vector2& rhs) const;
	Vector2 operator-(const Vector2& rhs) const;
	Vector2 operator*(float rhs) const;
	Vector2 operator/(float rhs) const;

	void operator+=(const Vector2& rhs);
	void operator-=(const Vector2& rhs);
	void operator/=(float rhs);
	void operator*=(float rhs);

	static float Distance(Vector2 left, Vector2 right);
	Vector2 Normalized() const;
	float Magnitude() const;

	float x;
	float y;
};

#endif