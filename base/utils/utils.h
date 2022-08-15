#pragma once
#define NOMINMAX
#include "vector/vector2d.h"
#include "security/xorstr.h"
#include "../hack/data.h"
#include <cstdint>
#include <vector>
#include "windows.h"

class utilities {
public:
	template <typename T = std::uint64_t>
	bool valid_ptr(T ptr) {
		return (ptr && ptr > (T)0xFFFFFF && ptr < (T)0x7FFFFFFFFFFF);
	}

	// credits: qo0 https://github.com/rollraw/qo0-base/blob/f6ded6392dbb9e433c279fdb6fc3843398b9e1c7/base/utilities/memory.h#L123-L128
	template <typename T, typename ... args_t>
	constexpr T call_vfunc(void* thisptr, std::size_t index, args_t... args) {
		using fn = T(__thiscall*)(void*, decltype(args)...);
		return (*static_cast<fn**>(thisptr))[index](thisptr, args...);
	}

	uintptr_t signature(const std::string& signature);
};

extern utilities g_utils;