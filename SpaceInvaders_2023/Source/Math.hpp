#pragma once
#include "raylib.h"
#include <cmath>
#include <format>

struct Size {
	Size() {}
	Size(int w, int h) : width(w), height(h) {}
	Size(Vector2 &size) : width(size.x), height(size.y) {}
	int width, height;
};

inline Vector2 operator+(Vector2& lhs, Vector2& rhs) { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline Vector2 operator-(Vector2& lhs, Vector2& rhs) { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }

inline float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

	return length;
}

inline bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <>
struct std::formatter<Vector2> {
	constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
	auto format(const Vector2& v, std::format_context& ctx) const { return std::format_to(ctx.out(), "(x: {}, y: {})", v.x, v.y); }
};
