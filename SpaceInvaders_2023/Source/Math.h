#pragma once
#include "raylib.h"
#include <cmath>
#include <format>

struct Size {
	Size(int w, int h) : width(w), height(h) {}
	Size(Vector2 &size) : width(size.x), height(size.y) {}
	int width, height;
};

struct Circle {
	Vector2 center;
	float radius;
};

template <typename T>
T& clamp(T& value, T& min, T& max) { return (value > max) ? max : ( (value < min) ? min : value ); }

/* ==== Vector2 Operations ==== */

inline bool operator==(const Vector2& lhs, const Vector2& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y; }

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }

inline Vector2 operator*(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x * rhs, lhs.y * rhs}; }
inline Vector2 operator/(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x / rhs, lhs.y / rhs}; }
inline Vector2 operator*(float lhs, const Vector2& rhs) noexcept { return Vector2{rhs.x * lhs, rhs.y * lhs}; }
inline Vector2 operator/(float lhs, const Vector2& rhs) noexcept { return Vector2{rhs.x / lhs, rhs.y / lhs}; }

/* ==== Rectangle Operations ==== */

inline Rectangle operator+(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width + rhs.width, lhs.height + rhs.height}; }
inline Rectangle operator-(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x - rhs.x, lhs.y - rhs.y, lhs.width - rhs.width, lhs.height - rhs.height}; }

inline Rectangle operator*(const Rectangle& lhs, float rhs) noexcept 		{ return Rectangle{lhs.x, lhs.y, lhs.width * rhs, lhs.height * rhs}; }
inline Rectangle operator/(const Rectangle& lhs, float rhs) noexcept 		{ return Rectangle{lhs.x, lhs.y, lhs.width / rhs, lhs.height / rhs}; }
inline Rectangle operator+(const Rectangle& lhs, const Vector2& rhs) noexcept	{ return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width, lhs.height}; }

inline Rectangle getRect(float width, float height) noexcept 			{ return Rectangle{0,0, width, height}; }
inline Vector2 getCenter(const Rectangle& rect) noexcept 				{ return Vector2(rect.width, rect.height) / 2.0f; }

template <>
struct std::formatter<Vector2> {
	constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }
	auto format(const Vector2& v, std::format_context& ctx) const { return std::format_to(ctx.out(), "(x: {}, y: {})", v.x, v.y); }
};
