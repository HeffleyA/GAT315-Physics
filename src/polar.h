#pragma once
#include <raymath.h>

struct polar
{
public:
	polar() = default;
	polar(float angle, float radius) :
		angle{ angle },
		radius{ radius }
	{
	}

	polar(const Vector2& v) :
		angle{ (float)atan(v.y / v.x) }, //!!get angle from Vector2 !!
		radius{ (float)sqrt((v.x * v.x) + (v.y * v.y)) } //!!get vector length !!
	{
	}

	polar& operator = (const Vector2& v)
	{
		angle = atan(v.y / v.x); //!!get angle from Vector2 !!;
		radius = sqrt((v.x * v.x) + (v.y * v.y)); //!!get vector length !!;

		return *this;
	}

	operator Vector2() const
	{
		Vector2 v;
		v.x = cos(angle) * radius; //!!get x position using cos(angle)* radius !!;
		v.y = sin(angle) * radius; //!!get y position using sin(angle)* radius !!;

		return v;
	}

public:
	float angle{ 0 };
	float radius{ 0 };
};