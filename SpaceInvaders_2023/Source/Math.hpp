//
//  Math.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#ifndef Math_hpp
#define Math_hpp
#include "raylib.h"
#include <cmath>


// ====
Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept; /* { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }*/
Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept; /* { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }*/
float magnitude(const Vector2& v) noexcept;
// ====

// ====
struct Circle {
	Vector2 position;
	float radius;
	bool contains(const Vector2& point) const noexcept { Vector2 d = point - position; return magnitude(d) < radius; }
};
// ====


float lineLength(Vector2 A, Vector2 B); //Uses pythagoras to calculate the length of a line
// A Line has infinite length, so this is technically a LineSegment defined by Points A and B, which are defined in terms of Vectors OA and OB, we could instead take the length of Vector OB - OA = AB, i.e. magnitude of B-A
//{
//	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
//	return length;
//}

bool pointInCircle(const Circle& circle, Vector2 point);
bool pointInCircle(Vector2 circlePos, float radius, Vector2 point); // Uses pythagoras to calculate if a point is within a circle or not

#endif /* Math_hpp */
