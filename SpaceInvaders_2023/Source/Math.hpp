//
//  Math.hpp
//  SpaceInvaders_2023
//
//  Created by Carl Swanberg on 2025-12-19.
//

#ifndef Math_hpp
#define Math_hpp
#include <raylib.h>
#include <cmath>
#include <format>

struct scale {
	explicit scale(const Rectangle &rect) : width(rect.width), height(rect.height) {}
	explicit scale(Vector2 v) : width(v.x), height(v.y) {}
	explicit scale(float w, float h) : width(w), height(h) {}
	explicit scale(float s) : width(s), height(s) {}

	float width;
	float height;

	explicit operator Vector2() const noexcept { return Vector2(width, height); }
	explicit operator Rectangle() const noexcept { return Rectangle{ 0, 0, width, height }; }
};

struct point {
	point(const Vector2 &v) : x(v.x), y(v.y) {}
	point(float px, float py) : x(px), y(py) {}
	float x;
	float y;
	//explicit operator Vector2() const noexcept { return Vector2{x, y}; }
	explicit operator Vector2() const noexcept { return Vector2{x, y}; }

	point operator+(const Vector2& other) const noexcept { return point(x + other.x, y + other.y); }
	point operator+(const point& other) const noexcept { return point(x + other.x, y + other.y); }
	point operator-(const Vector2& other) const noexcept { return point(x - other.x, y - other.y); }
	Vector2 operator-(const point& other) const noexcept { return Vector2(x - other.x, y - other.y); }
};

//struct Vector2i {
//	int x;
//	int y;
//	explicit operator Vector2() const noexcept { return Vector2{static_cast<float>(x), static_cast<float>(y)}; }
//};

struct Circle {
	point position;
	float radius = 1;
};

// ====

inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }

inline Vector2 operator*(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x * rhs, lhs.y * rhs}; }
inline Vector2 operator/(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x / rhs, lhs.y / rhs}; }

//inline float hypot(float x, float y) { return sqrtf(x * x + y * y); }
inline float magnitude(const Vector2& v) noexcept { return hypot(v.x, v.y); }
inline Vector2 unit(const Vector2& v) { return v / magnitude(v); }
inline float dot(const Vector2& lhs, const Vector2& rhs) noexcept { return lhs.x * rhs.x + lhs.y * rhs.y; }

inline Rectangle getBounds(const Rectangle& rect, const point &p) { return Rectangle{ p.x, p.y, rect.width, rect.height}; }
inline Rectangle getBounds(const point& p, const scale &s) { return Rectangle{ p.x, p.y, s.width, s.height}; }
inline Rectangle getBounds(float width, float height) { return Rectangle{ 0, 0, width, height}; }
inline Rectangle getBounds(int width, int height) { return Rectangle{ 0, 0, static_cast<float>(width), static_cast<float>(height)}; }
inline Rectangle getBounds(float size) { return Rectangle{ 0, 0, size, size}; }

inline Rectangle operator+(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width + rhs.width, lhs.height + rhs.height}; }
inline Rectangle operator-(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x - rhs.x, lhs.y - rhs.y, lhs.width - rhs.width, lhs.height - rhs.height}; }
inline Rectangle operator*(const Rectangle& lhs, float rhs) noexcept { return Rectangle{lhs.x, lhs.y, lhs.width * rhs, lhs.height * rhs}; }
inline Rectangle operator/(const Rectangle& lhs, float rhs) noexcept { return Rectangle{lhs.x, lhs.y, lhs.width / rhs, lhs.height / rhs}; }

inline Rectangle operator+(const Rectangle& lhs, const Vector2& rhs) noexcept { return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width, lhs.height}; }
inline Rectangle operator+(const Rectangle& lhs, const point& rhs) noexcept { return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width, lhs.height}; }
inline Vector2 getSizeVector(const Rectangle& rect) { return Vector2(rect.width, rect.height ); }
inline Vector2 getPositionVector(const Rectangle& rect) { return Vector2(rect.x, rect.y ); }
inline Vector2 getCenter(const Rectangle& rect) { return getPositionVector(rect) + getSizeVector(rect) / 2; }

struct LineSegment {
	LineSegment(const Vector2 &vs, const Vector2 &ve) : start(point(vs)), end(point(ve)) {}
	LineSegment(const point &ps, const point &pe) : start(ps), end(pe) {}
	point start;
	point end;
	float length() const noexcept { return magnitude(end - start); }
	Vector2 direction() { if(length() == 0) return Vector2{0, 0}; return unit(end - start); }
	explicit operator Vector2() { return end - start; }
	//bool contains(const point& p);
};


inline float length(const LineSegment& line) noexcept { return line.length(); }
inline float distance(const Vector2& lhs, const Vector2& rhs) { return magnitude(rhs - lhs); }

// ====

bool pointInCircle(const Circle& circle, const point& point);
bool pointInCircle(const point& circlePos, float radius, const point& point); // Uses pythagoras to calculate if a point is within a circle or not

//original math functions
bool pointInCircle(Vector2 circlePos, float radius, Vector2 point);
float lineLength(Vector2 A, Vector2 B); //Uses pythagoras to calculate the length of a line
						    // A Line has infinite length, so this is technically a LineSegment defined by Points A and B, which are defined in terms of Vectors OA and OB, we could instead take the length of Vector OB - OA = AB, i.e. magnitude of B-A

// ====


//Print Vector2
template <>
struct std::formatter<Vector2> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const Vector2& v, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "(X: {}, Y: {})", v.x, v.y);
	}
};

template <>
struct std::formatter<point> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const point& p, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "(X: {}, Y: {})", p.x, p.y);
	}
};

#endif /* Math_hpp */
