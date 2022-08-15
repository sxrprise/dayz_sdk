#pragma once
#include "../vector/vector.h"
#include "../vector/vector2d.h"
#include <cstdlib>
#include <algorithm>

class math {
public:
    float pi = 3.1415926535897932384f;
    float pi_2 = pi * 2;            

    __forceinline constexpr float deg_to_rad(float val) {
        return val * (pi / 180.f);
    }

    __forceinline constexpr float rad_to_deg(float val) {
        return val * (180.f / pi);
    }

    template <typename T = float>
    __forceinline void clamp(T& value, T min, T max) {
        value = (std::max)(min, (std::min)(value, max));
    }
};

extern math g_math;