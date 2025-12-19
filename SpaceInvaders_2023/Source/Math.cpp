//
//  Math.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#include "Math.hpp"
#include "raylib.h"

Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
Vector2 operator-(const Vector2& lhs, Vector2& rhs) noexcept { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }
float magnitude(const Vector2& v) noexcept { return sqrtf(v.x * v.x + v.y * v.y); }  //sqrt(x^2 + y^2)

float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

	return length;
}

bool pointInCircle(const Circle& circle, Vector2 point) {
	Vector2 displacement = point - circle.position;
	float distanceToCircle = magnitude(displacement);

	return (distanceToCircle < circle.radius);
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
{
	Vector2 displacement = point - circlePos;
	float distanceToCircle = magnitude(point - circlePos);

	return (distanceToCircle < radius);
}

//
//bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
//{
//	float distanceToCentre = lineLength(circlePos, point);
//
//	if (distanceToCentre < radius)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
