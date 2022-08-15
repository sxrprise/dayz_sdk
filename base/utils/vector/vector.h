#pragma once
#include <sstream>
#include <DirectXMath.h>

class vector {
public:
	float x, y, z;

	__forceinline vector() {
		this->x = 0.f;
		this->y = 0.f;
		this->z = 0.f;
	}

	__forceinline vector(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	__forceinline vector(DirectX::XMFLOAT3 vec) {
		this->x = vec.x;
		this->y = vec.y;
		this->z = vec.z;
	}

	__forceinline bool operator==(const vector& v) const {
		return v.x == x && v.y == y && v.z == z;
	}

	__forceinline bool operator!=(const vector& v) const {
		return v.x != x || v.y != y || v.z != z;
	}

	__forceinline vector& operator+=(const vector& other) {
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	__forceinline vector& operator-=(const vector& other) {
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	__forceinline vector& operator*=(const vector& other) {
		x *= other.x;
		y *= other.y;
		z *= other.z;

		return *this;
	}

	__forceinline vector& operator/=(const vector& other) {
		x /= other.x;
		y /= other.y;
		z /= other.z;

		return *this;
	}

	__forceinline vector& operator+=(float fl) {
		x += fl;
		y += fl;
		z += fl;

		return *this;
	}

	__forceinline vector& operator*=(float fl) {
		x *= fl;
		y *= fl;
		z *= fl;

		return *this;
	}

	__forceinline vector operator+(const vector& other) {
		return { x + other.x, y + other.y, z + other.z };
	}

	__forceinline vector operator-(const vector& other) {
		return { x - other.x, y - other.y, z - other.z };
	}

	__forceinline vector operator+(const float& other) {
		return { x + other, y + other, z + other };
	}

	__forceinline vector operator-(const float& other) {
		return { x - other, y - other, z - other };
	}

	auto operator+(const vector& other) const -> vector {
		auto buf = *this;

		buf.x += other.x;
		buf.y += other.y;
		buf.z += other.z;

		return buf;
	}

	auto operator-(const vector& other) const -> vector {
		auto buf = *this;

		buf.x -= other.x;
		buf.y -= other.y;
		buf.z -= other.z;

		return buf;
	}

	auto operator*(const float& fl) const -> vector {
		auto buf = *this;

		buf.x *= fl;
		buf.y *= fl;
		buf.z *= fl;

		return buf;
	}

	auto operator-() {
		return vector(
			-x,
			-y,
			-z
		);
	}

	__forceinline vector operator*(float fl) {
		return { x * fl, y * fl, z * fl };
	}

	__forceinline vector operator*(const vector& other) {
		return { x * other.x, y * other.y, z * other.z };
	}

	__forceinline vector& operator/=(float fl) {
		x /= fl;
		y /= fl;
		z /= fl;

		return *this;
	}

	__forceinline auto operator/(float other) {
		vector buf;

		buf.x = x / other;
		buf.y = y / other;
		buf.z = z / other;

		return buf;
	}

	__forceinline float& operator[](int i) {
		return ((float*)this)[i];
	}

	__forceinline float operator[](int i) const {
		return ((float*)this)[i];
	}

	__forceinline float length_2d() {
		return sqrt((x * x) + (y * y));
	}

	__forceinline float length_sqr() {
		return this->dot(*this);
	}

	__forceinline bool is_zero() {
		return x == 0 && y == 0 && z == 0;
	}

	__forceinline float length() const {
		auto vec = *this;
		return std::sqrt(vec.length_sqr());
	}

	__forceinline vector cross(const vector& v) {
		return vector(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	__forceinline float dot(const vector& v) const {
		return (x * v.x + y * v.y + z * v.z);
	}

	__forceinline float dot(const float* other) {
		const vector& a = *this;

		return(a.x * other[0] + a.y * other[1] + a.z * other[2]);
	}

	__forceinline float dist_to(const vector& to) const {
		vector delta;

		delta.x = x - to.x;
		delta.y = y - to.y;
		delta.z = z - to.z;

		return delta.length();
	}

	__forceinline vector normalized() const {
		vector vec = *this;
		vec.normalize_in_place();
		return vec;
	}

	__forceinline float normalize_in_place() {
		const float length = this->length();
		const float radius = 1.0f / (length + std::numeric_limits<float>::epsilon());

		this->x *= radius;
		this->y *= radius;
		this->z *= radius;

		return length;
	}

	__forceinline vector lerp(vector to, float multiplier) {
		return vector(
			this->x + static_cast<int>(multiplier * (to.x - this->x)),
			this->y + static_cast<int>(multiplier * (to.y - this->y)),
			this->z + static_cast<int>(multiplier * (to.z - this->z))
		);
	}

	__forceinline vector rotate(float distance, float angle) {
		constexpr float pi = 3.14159265358979323846f;

		return vector(
			this->x + cos((angle * (pi / 180.f))) * distance,
			this->y + sin((angle * (pi / 180.f))) * distance,
			this->z
		);
	}
};