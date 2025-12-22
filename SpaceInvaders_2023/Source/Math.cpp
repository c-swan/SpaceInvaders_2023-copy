//
//  Math.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//
#include "raylib.h"
#include "Math.hpp"

bool pointInRect(const Rectangle& rect, const Vector2& point) {
	return !(point.x < rect.x || point.y < rect.y || point.x > rect.x + rect.width || point.y > rect.y + rect.height);
}

bool circleInCircle(const Circle& circle1, const Circle& circle2) {
	return distance(circle2.position, circle2.position) < circle1.radius + circle2.radius; //right?
}
bool pointInCircle(const Circle& circle, const Vector2& point) {
	return distance(circle.position, point) < circle.radius;
}

bool pointOnLine(const LineSegment& line, const Vector2& point) {
	Vector2 proj = projectOnto(point - line.start, line.end - point);
	float segmentLengths = distance(proj, line.start) + distance(proj, line.end);
	return segmentLengths <= line.length();
}

/**
* 			       v•u     u	    v•u	         v•u
* 	proj_v(û) = (v•û)û = ––––   ––   =   ––––– u =  ––––– u
* 			       ||u||   ||u||	   ||u||²	         u•u
*
 */
Vector2 projectOnto(const Vector2& a, const Vector2& b) {
	Vector2 proj = dot(a, b) / dot(b, b) * b;
	return proj;
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
