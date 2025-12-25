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

struct Scale {
	float width;
	float height;
	explicit operator Vector2() { return Vector2(width, height); } //size vector
	explicit operator Rectangle() { return Rectangle(0, 0, width, height); } //size vector
};

/* ==== Vector2 Operations ==== */

inline bool operator==(const Vector2& lhs, const Vector2& rhs) noexcept { return lhs.x == rhs.x && lhs.y == rhs.y; }
//inline bool operator!=(const Vector2& lhs, const Vector2& rhs) noexcept { return !(lhs == rhs); }


inline Vector2 operator+(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x + rhs.x, lhs.y + rhs.y); }
inline Vector2 operator-(const Vector2& lhs, const Vector2& rhs) noexcept { return Vector2(lhs.x - rhs.x, lhs.y - rhs.y); }

inline Vector2 operator*(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x * rhs, lhs.y * rhs}; }
inline Vector2 operator/(const Vector2& lhs, float rhs) noexcept { return Vector2{lhs.x / rhs, lhs.y / rhs}; }
inline Vector2 operator*(float lhs, const Vector2& rhs) noexcept { return Vector2{rhs.x * lhs, rhs.y * lhs}; }
inline Vector2 operator/(float lhs, const Vector2& rhs) noexcept { return Vector2{rhs.x / lhs, rhs.y / lhs}; }

inline Rectangle operator+(const Scale& lhs, const Vector2& rhs) noexcept 	{ return Rectangle{rhs.x, rhs.y, lhs.width, lhs.height}; }
inline Rectangle operator+(const Vector2& lhs, const Scale& rhs) noexcept 	{ return Rectangle{lhs.x, lhs.y, rhs.width, rhs.height}; }

inline float magnitude(const Vector2& v) noexcept 						{ return hypot(v.x, v.y); }
inline float dot(const Vector2& lhs, const Vector2& rhs) noexcept				{ return lhs.x * rhs.x + lhs.y * rhs.y; }
inline float distance(const Vector2& lhs, const Vector2& rhs) 				{ return magnitude(rhs - lhs); }
inline Vector2 unit(const Vector2& v) 								{ return v / magnitude(v); } //can throw except if magnitude 0

/* ==== Rectangle Operations ==== */

inline Rectangle operator+(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width + rhs.width, lhs.height + rhs.height}; }
inline Rectangle operator-(const Rectangle& lhs, const Rectangle& rhs) noexcept { return Rectangle{lhs.x - rhs.x, lhs.y - rhs.y, lhs.width - rhs.width, lhs.height - rhs.height}; }

inline Rectangle operator*(const Rectangle& lhs, float rhs) noexcept 		{ return Rectangle{lhs.x, lhs.y, lhs.width * rhs, lhs.height * rhs}; }
inline Rectangle operator/(const Rectangle& lhs, float rhs) noexcept 		{ return Rectangle{lhs.x, lhs.y, lhs.width / rhs, lhs.height / rhs}; }
inline Rectangle operator+(const Rectangle& lhs, const Vector2& rhs) noexcept	{ return Rectangle{lhs.x + rhs.x, lhs.y + rhs.y, lhs.width, lhs.height}; }
inline Rectangle operator+(const Rectangle& lhs, const Scale& rhs) noexcept	{ return Rectangle{lhs.x, lhs.y, lhs.width + rhs.width, lhs.height + rhs.height}; }

inline Rectangle getBounds(const Vector2& pos, const Vector2 &scale) noexcept 	{ return Rectangle{ pos.x, pos.y, scale.x, scale.y }; }
inline Rectangle getBounds(const Vector2 &scale)  noexcept					{ return Rectangle {0, 0, scale.x, scale.y}; }
inline Rectangle getBounds(const Scale &scale)  noexcept					{ return Rectangle {0, 0, scale.width, scale.height}; }
inline Rectangle getBounds(float x, float y, float width, float height)  noexcept 	{ return Rectangle{ x, y, width, height}; }
inline Rectangle getBounds(float width, float height) noexcept 				{ return Rectangle{ 0, 0, width, height}; }
inline Rectangle getBounds(float size) noexcept 						{ return Rectangle{ 0, 0, size, size}; }

inline Vector2 getSizeVector(const Rectangle& rect) noexcept 				{ return Vector2(rect.width, rect.height ); }
inline Vector2 getPositionVector(const Rectangle& rect) noexcept 				{ return Vector2(rect.x, rect.y ); }
inline Vector2 getCenter(const Rectangle& rect) noexcept 					{ return getPositionVector(rect) + getSizeVector(rect) / 2; }

/* ==== LineSegment ==== */

struct LineSegment {
	Vector2 start;
	Vector2 end;
	float length() const noexcept { return magnitude(end - start); }
	explicit operator Vector2() { return end - start; }
};

struct Circle {
	Vector2 position;
	float radius;
};

bool floatInRange(float value, float min, float max);
bool lineOnLine(const LineSegment& line1, const LineSegment& line2);
inline bool pointOnPoint(const Vector2& p1, const Vector2& p2) { return p1 == p2; }
bool pointOnLine(const LineSegment& line, const Vector2& point);
bool pointInCircle(const Circle& circle, const Vector2& point);
bool pointInRect(const Rectangle& rect, const Vector2& point);
//bool rectInRect(const Rectangle& rect1, const Rectangle& rect2);
/**
 *
 * \param A vector which is projected onto B
 * \param B vector onto which A is projected
 */
Vector2 projectOnto(const Vector2& A, const Vector2& B);


bool CheckCollision(const Circle& circle, const LineSegment& line);



//original math functions
//bool pointInCircle(Vector2 circlePos, float radius, Vector2 point);
//float lineLength(Vector2 A, Vector2 B);
//Uses pythagoras to calculate the length of a line
						    // A Line has infinite length, so this is technically a LineSegment defined by Points A and B, which are defined in terms of Vectors OA and OB, we could instead take the length of Vector OB - OA = AB, i.e. magnitude of B-A

// ====


//Print Vector2
template <>
struct std::formatter<Vector2> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const Vector2& v, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "(x: {}, y: {})", v.x, v.y);
	}
};

template <>
struct std::formatter<Scale> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const Scale& s, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "(width: {}, height: {})", s.width, s.height);
	}
};


template <>
struct std::formatter<Rectangle> {
	constexpr auto parse(std::format_parse_context& ctx) {
		return ctx.begin();
	}

	auto format(const Rectangle& r, std::format_context& ctx) const {
		return std::format_to(ctx.out(), "(x: {}, y: {}, width: {}, height: {})", r.x, r.y, r.width, r.height);
	}
};

#endif /* Math_hpp */
