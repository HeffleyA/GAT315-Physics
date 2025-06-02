#pragma once
#include "raylib.h"
#include "raymath.h"

struct AABB
{
	Vector2 center;
	Vector2 size;

	AABB(const Vector2& center, const Vector2& size) : 
		center{ center },
		size{ size }
	{}

	Vector2 extents() const { return size / 2; }
	Vector2 min() const { return Vector2Subtract(center, extents()); }
	Vector2 max() const { return Vector2Add(center, extents()); }
};