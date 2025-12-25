//
//  Math.cpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//
#include "raylib.h"
#include "Math.hpp"

bool lineOnLine(const LineSegment& line1, const LineSegment& line2) {
	return pointOnLine(line1, line2.start) || pointOnLine(line1, line2.end) || pointOnLine(line2, line1.start) || pointOnLine(line2, line1.end);
}

bool rectInRect(const Rectangle& rect1, const Rectangle& rect2) {
	bool f1 = floatInRange(rect1.x, rect2.x, rect2.width);
	bool f2 = floatInRange(rect2.x, rect1.x, rect1.width);
	bool f3 = floatInRange(rect1.y, rect2.y, rect2.height);
	bool f4 = floatInRange(rect2.y, rect1.y, rect1.height);

	return (f1 && f2 && f3 && f4);
}

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

bool CheckCollision(const Circle& circle, const LineSegment& line) {
	if (pointInCircle(circle, line.start) || pointInCircle(circle, line.end)) { return true; }
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
