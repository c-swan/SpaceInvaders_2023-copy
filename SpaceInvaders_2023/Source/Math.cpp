//
//  Math.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//
#include "raylib.h"
#include "Math.hpp"

bool pointInCircle(const Circle& circle, const point& point) {
	LineSegment circleToPoint { circle.position, point };
	float distanceToCircle = circleToPoint.length();
	return (distanceToCircle < circle.radius);
}


bool pointInCircle(const point& circlePos, float radius, const point& point) { // Uses pythagoras to calculate if a point is within a circle or not

	return pointInCircle(Circle(circlePos, radius), point);
}


//Original Math Functions
float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));

	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius) //TODO: simplify
	{
		return true;
	}
	else
	{
		return false;
	}
}
