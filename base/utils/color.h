#pragma once
#include <algorithm>
#include <chrono>
#include <string>
#include <d3d9.h>
#include "math/math.h"

// credits: philip015 https://github.com/notphage/fatality.win/blob/7f37a93a3e3974c18979d8bd5c2ccc7e1a3ca4a3/internal_hvh/sdk/datatypes/Color.h
class color {
public:
	color() {
		*((int*)this) = 0;
	}
	
	color(int _r, int _g, int _b) {
		set_color(_r, _g, _b, 255);
	}
	
	color(int _r, int _g, int _b, int _a) {
		set_color(_r, _g, _b, _a);
	}
	
	color(float _rgb[3]) {
		set_color((int)(_rgb[0] * 255.f), (int)(_rgb[1] * 255.f), (int)(_rgb[2] * 255.f), 255);
	}
	
	color(float _rgb[3], float _alpha) {
		set_color((int)(_rgb[0] * 255.f), (int)(_rgb[1] * 255.f), (int)(_rgb[2] * 255.f), (int)_alpha);
	}

	color(const uint32_t val) {
		set_color(
			(val >> 24),
			(val >> 16) & 0xFF,
			(val >> 8) & 0xFF,
			val & 0xFF
		);
	}

	color(color _cl, float _alpha) {
		set_color((int)_cl.r(), (int)_cl.g(), (int)_cl.b(), (int)_alpha);
	}

	void set_color(int _r, int _g, int _b, int _a = 255) {
		_cl[0] = (unsigned char)_r;
		_cl[1] = (unsigned char)_g;
		_cl[2] = (unsigned char)_b;
		_cl[3] = (unsigned char)_a;
	}

	void get_color(int& _r, int& _g, int& _b, int& _a) const {
		_r = _cl[0];
		_g = _cl[1];
		_b = _cl[2];
		_a = _cl[3];
	}

	void set_raw_color(int color32) {
		*((int*)this) = color32;
	}

	int get_raw_color() const {
		return *((int*)this);
	}

	D3DCOLOR to_d3d() const {
		return D3DCOLOR_ARGB(a(), r(), g(), b());
	}

	inline int r() const { return _cl[0]; }
	inline int g() const { return _cl[1]; }
	inline int b() const { return _cl[2]; }
	inline int a() const { return _cl[3]; }

	inline float r_base() const { return _cl[0] / 255.f; }
	inline float g_base() const { return _cl[1] / 255.f; }
	inline float b_base() const { return _cl[2] / 255.f; }
	inline float a_base() const { return _cl[3] / 255.f; }

	unsigned char& operator[](int index) {
		return _cl[index];
	}

	const unsigned char& operator[](int index) const {
		return _cl[index];
	}

	bool operator == (const color& rhs) const {
		return (*((int*)this) == *((int*)&rhs));
	}

	bool operator != (const color& rhs) const {
		return !(operator==(rhs));
	}

	color& operator=(const color& rhs) {
		set_raw_color(rhs.get_raw_color());
		return *this;
	}

	__forceinline color alpha(float alpha) {
		return color(r(), g(), b(), static_cast<int>(alpha));
	}

	__forceinline color scale_alpha(float alpha) {
		g_math.clamp(alpha, 0.f, 1.f);
		return color(r(), g(), b(), static_cast<int>(a() * alpha));
	}

	float hue() const {
		if (_cl[0] == _cl[1] && _cl[1] == _cl[2]) {
			return 0.f;
		}

		float r = _cl[0] / 255.f;
		float g = _cl[1] / 255.f;
		float b = _cl[2] / 255.f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.f;

		if (r == max) {
			hue = (g - b) / delta;
		}
		else if (g == max) {
			hue = 2 + (b - r) / delta;
		}
		else if (b == max) {
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.f) {
			hue += 360.f;
		}
		return hue;
	}

	float saturation() const {
		float r = _cl[0] / 255.f;
		float g = _cl[1] / 255.f;
		float b = _cl[2] / 255.f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;

		float delta = max - min;

		if (max == 0.f)
			return delta;

		return delta / max;
	}

	float brightness() const {
		float r = _cl[0] / 255.f;
		float g = _cl[1] / 255.f;
		float b = _cl[2] / 255.f;

		float max = r > g ? r : g > b ? g : b;

		return max;
	}

	// same as ImGui::ColorConvertHSVtoRGB
	static color from_hsb(float hue, float saturation, float brightness) {
		float out_r, out_g, out_b;
		if (saturation == 0.f) {
			// gray
			out_r = out_g = out_b = brightness;
			return color(int(out_r * 255), int(out_g * 255), int(out_b * 255));
		}

		hue = fmodf(hue, 1.f) / (60.f / 360.f);
		int   i = (int)hue;
		float f = hue - (float)i;
		float p = brightness * (1.f - saturation);
		float q = brightness * (1.f - saturation * f);
		float t = brightness * (1.f - saturation * (1.f - f));

		switch (i) {
			case 0: out_r = brightness; out_g = t; out_b = p; break;
			case 1: out_r = q; out_g = brightness; out_b = p; break;
			case 2: out_r = p; out_g = brightness; out_b = t; break;
			case 3: out_r = p; out_g = q; out_b = brightness; break;
			case 4: out_r = t; out_g = p; out_b = brightness; break;
			case 5: default: out_r = brightness; out_g = p; out_b = q; break;
		}

		return color(int(out_r * 255), int(out_g * 255), int(out_b * 255));
	}

	// same as ImGui::ColorConvertRGBtoHSV
	static void to_hsb(color col, float& hue, float& saturation, float& brightness) {
		float K = 0.f;
		float r = col.r() / 255.f;
		float g = col.g() / 255.f;
		float b = col.b() / 255.f;

		if (g < b) {
			const float tmp = g; g = b; b = tmp;
			K = -1.f;
		}
		if (r < g) {
			const float tmp = r; r = g; g = tmp;
			K = -2.f / 6.f - K;
		}

		const float chroma = r - (g < b ? g : b);
		hue = fabsf(K + (g - b) / (6.f * chroma + 1e-20f));
		saturation = chroma / (r + 1e-20f);
		brightness = r;
	}

	static color from_hex(std::string hex) {
		std::string text = hex;
		int r, g, b, a;

		// remove that stupid ass useless header
		if (strstr(hex.c_str(), "#"))
			hex.erase(0, 1);

		// if we potentially have an alpha channel
		if (hex.length() > 6) {
			sscanf_s(hex.c_str(), "%02x%02x%02x%02x", &r, &g, &b, &a);
			return color(r, g, b, a);
		}

		sscanf_s(hex.c_str(), "%02x%02x%02x", &r, &g, &b);
		a = 255;

		return color(r, g, b, a);
	}

	static std::string to_hex(color col) {
		std::stringstream ss = {};
		ss << std::hex << (col.r() << 24 | col.g() << 16 | col.b() << 8 | col.a());
		return ss.str();
	}

	__forceinline color lerp(color to, float strength) {
		g_math.clamp(strength, 0.f, 1.f);

		return color(
			static_cast<int>((to.r() - this->r()) * strength) + this->r(),
			static_cast<int>((to.g() - this->g()) * strength) + this->g(),
			static_cast<int>((to.b() - this->b()) * strength) + this->b(),
			static_cast<int>((to.a() - this->a()) * strength) + this->a()
		);
	}

	__forceinline color saturate(float strength) {
		return color(
			std::clamp(static_cast<int>(this->r() * strength), 0, 255),
			std::clamp(static_cast<int>(this->g() * strength), 0, 255),
			std::clamp(static_cast<int>(this->b() * strength), 0, 255),
			this->a()
		);
	}
	
private:
	unsigned char _cl[4];
};