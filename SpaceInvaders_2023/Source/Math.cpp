//
//  Math.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//
#include "raylib.h"
#include "Math.hpp"

bool pointOnLine(const LineSegment& line, const Vector2& point) {
	Vector2 proj = projectOnto(point - line.start, line.end - point);
	float segmentLengths = distance(proj, line.start) + distance(proj, line.end);
	return segmentLengths <= line.length();
}


bool CheckCollision(const Circle& circle, const LineSegment& line) {
	if (CheckCollision(circle, line.start) || CheckCollision(circle, line.end)) { return true; }
	/*
	 A = line.start, B = line.end, C = circle.position, P = closestPoint
	 AP = proj_AB(AC) ,  P = proj_AB(AC) + A
	 oproj_u(v) = v - proj_u(v)
	 oproj_AB(AC) = AC - proj_AB(AC) = PC = -CP
	 */

	Vector2 closestPoint = projectOnto( circle.position - line.start, line.end - line.start) + line.start; //get closest point AP on line AB by projecting AC onto AB and adding A

	float segmentLengths = distance(closestPoint, line.start) + distance(closestPoint, line.end);
	float errorMargin = 0.1f;
	if(segmentLengths > line.length() + errorMargin) { //should be equal: |AP| + |PB| = |AB|
		return false;
	}
	if(segmentLengths < line.length()) {
		throw std::logic_error("Line projection length sum should not be less than line segment length");
	}
	Vector2 orthogonalProj = circle.position - closestPoint;
	/* closestPoint = proj_AB(AC) + line.start; we are already subtracting line.start to get the orthogonal projection vector, so oproj_AB(AC) = AC - proj_AB(AC) = orthogonalProj = (circle.position - line.start) - proj_AB(AC) = circle.position - closestPoint; */
	return magnitude(orthogonalProj) < circle.radius;
}


//Original Math Functions
//float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
//{
//	float length = sqrtf(pow(B.x - A.x, 2) + pow(B.y - A.y, 2));
//	return length;
//}

//bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
//{
//	float distanceToCentre = lineLength(circlePos, point);
//
//	if (distanceToCentre < radius) //TODO: simplify
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
