#pragma once
#include <limits>

// 2d vector for screen coordinates, maybe make it use integers since we cant have half pixels
class vector_2d {
public:
	float x, y;

public:
	// ctors
	__forceinline vector_2d(void) {}
	__forceinline vector_2d(float x, float y) : x{ x }, y{ y } {}
	__forceinline vector_2d(int x, int y) : x{ (float)x }, y{ float(y) } {}

	// at-accesors.
	__forceinline float& at(const size_t index) {
		return ((float*)this)[index];
	}
	__forceinline float& at(const size_t index) const {
		return ((float*)this)[index];
	}

	// index operators.
	__forceinline float& operator()(const size_t index) {
		return at(index);
	}
	__forceinline const float& operator()(const size_t index) const {
		return at(index);
	}
	__forceinline float& operator[](const size_t index) {
		return at(index);
	}
	__forceinline const float& operator[](const size_t index) const {
		return at(index);
	}

	// equality operators.
	__forceinline bool operator==(const vector_2d& v) const {
		return v.x == x && v.y == y;
	}
	__forceinline bool operator!=(const vector_2d& v) const {
		return v.x != x || v.y != y;
	}

	// copy assignment.
	__forceinline vector_2d& operator=(const vector_2d& v) {
		x = v.x;
		y = v.y;
		return *this;
	}

	// negation-operator.
	__forceinline vector_2d operator-() const {
		return vector_2d(-x, -y);
	}

	// arithmetic operators.
	__forceinline vector_2d operator+(const vector_2d& v) const {
		return {
			x + v.x,
			y + v.y
		};
	}
	__forceinline vector_2d operator-(const vector_2d& v) const {
		return {
			x - v.x,
			y - v.y
		};
	}
	__forceinline vector_2d operator*(const vector_2d& v) const {
		return {
			x * v.x,
			y * v.y
		};
	}
	__forceinline vector_2d operator/(const vector_2d& v) const {
		return {
			x / v.x,
			y / v.y
		};
	}

	// compound assignment operators.
	__forceinline vector_2d& operator+=(const vector_2d& v) {
		x += v.x;
		y += v.y;
		return *this;
	}
	__forceinline vector_2d& operator-=(const vector_2d& v) {
		x -= v.x;
		y -= v.y;
		return *this;
	}
	__forceinline vector_2d& operator*=(const vector_2d& v) {
		x *= v.x;
		y *= v.y;
		return *this;
	}
	__forceinline vector_2d& operator/=(const vector_2d& v) {
		x /= v.x;
		y /= v.y;
		return *this;
	}

	// arithmetic operators w/ float
	__forceinline vector_2d operator+(float f) const {
		return {
			x + f,
			y + f
		};
	}
	__forceinline vector_2d operator-(float f) const {
		return {
			x - f,
			y - f
		};
	}
	__forceinline vector_2d operator*(float f) const {
		return {
			x * f,
			y * f
		};
	}
	__forceinline vector_2d operator/(float f) const {
		return {
			x / f,
			y / f
		};
	}

	// arithmetic operators w/ int
	__forceinline vector_2d operator+(int i) const {
		return {
			x + static_cast<float>(i),
			y + static_cast<float>(i)
		};
	}
	__forceinline vector_2d operator-(int i) const {
		return {
			x - static_cast<float>(i),
			y - static_cast<float>(i)
		};
	}
	__forceinline vector_2d operator*(int i) const {
		return {
			x * static_cast<float>(i),
			y * static_cast<float>(i)
		};
	}
	__forceinline vector_2d operator/(int i) const {
		return {
			x / static_cast<float>(i),
			y / static_cast<float>(i)
		};
	}

	// compound assignment operators w/ float
	__forceinline vector_2d& operator+=(float f) {
		x += f;
		y += f;
		return *this;
	}
	__forceinline vector_2d& operator-=(float f) {
		x -= f;
		y -= f;
		return *this;
	}
	__forceinline vector_2d& operator*=(float f) {
		x *= f;
		y *= f;
		return *this;
	}
	__forceinline vector_2d& operator/=(float f) {
		x /= f;
		y /= f;
		return *this;
	}

	// methods.
	__forceinline bool is_zero() {
		return x == 0 && y == 0;
	}

	__forceinline float length_sqr() const {
		return (x * x + y * y);
	}

	__forceinline float length() const {
		return static_cast<float>(sqrt(length_sqr()));
	}

	__forceinline float dist_to(const vector_2d& to) const {
		vector_2d delta;

		delta.x = x - to.x;
		delta.y = y - to.y;

		return delta.length();
	}

	/*__forceinline vector_2d rotate(float distance, float angle) {
		constexpr float pi = 3.14159265358979323846f;

		return vector_2d(
			this->x + cos((angle * (pi / 180.f))) * distance,
			this->y + sin((angle * (pi / 180.f))) * distance
		);
	}*/
};