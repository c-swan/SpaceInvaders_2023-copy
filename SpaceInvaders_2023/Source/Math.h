#pragma once
#include "raylib.h"
#include <cmath>
#include <format>

struct Circle {
	Vector2 center;
	float radius;
};

/* ==== Vector2 Operations ==== */

inline bool operator==(const Vector2& lhs, const Vector2& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y; }

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }

inline Vector2 operator*(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x * rhs, lhs.y * rhs}; }
inline Vector2 operator/(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x / rhs, lhs.y / rhs}; }
inline Vector2 operator*(float lhs, const Vector2& rhs) noexcept { return Vector2{rhs.x * lhs, rhs.y * lhs}; }
inline Vector2 operator/(float lhs, const Vector2& rhs) noexcept { return Vector2{rhs.x / lhs, rhs.y / lhs}; }

/* ==== Circle Operations ==== */
inline Circle operator+(const Circle& lhs, const Vector2& rhs) noexcept	{ return Circle({lhs.center.x + rhs.x, lhs.center.y + rhs.y}, lhs.radius); }

/* ==== Rectangle Operations ==== */

inline Rectangle operator+(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width + rhs.width, lhs.height + rhs.height}; }
inline Rectangle operator-(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x - rhs.x, lhs.y - rhs.y, lhs.width - rhs.width, lhs.height - rhs.height}; }

inline Rectangle operator*(const Rectangle& lhs, float rhs) noexcept 		{ return Rectangle{lhs.x, lhs.y, lhs.width * rhs, lhs.height * rhs}; }
inline Rectangle operator/(const Rectangle& lhs, float rhs) noexcept 		{ return Rectangle{lhs.x, lhs.y, lhs.width / rhs, lhs.height / rhs}; }
inline Rectangle operator+(const Rectangle& lhs, const Vector2& rhs) noexcept	{ return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width, lhs.height}; }

inline Rectangle getRect(float width, float height) noexcept 			{ return Rectangle{0,0, width, height}; }
inline Rectangle getRect(float size) noexcept			 			{ return Rectangle{0,0, size, size}; }
inline Vector2 getCenter(const Rectangle& rect) noexcept 				{ return Vector2(rect.width, rect.height) / 2.0f; }
inline Vector2 getPosition(const Rectangle& rect) noexcept 				{ return Vector2(rect.x, rect.y); }
