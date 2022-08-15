#pragma once
#include <d3d11.h>
#pragma comment(lib, "d3d11.lib")
#include "../../utils/utils.h"
#include "../../utils/console/console.h"
#include "../../utils/security/xorstr.h"
#include "../../dependencies/minhook/minhook.h"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/backends/imgui_impl_dx11.h"
#include "../../dependencies/imgui/backends/imgui_impl_win32.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "../../dependencies/imgui/imgui_internal.h"

#include <thread>
#include <dxgi.h>

namespace hooks
{
	void attach( );
	void detach( );
	auto hk_present( IDXGISwapChain* swapChain, UINT syncInterval, UINT flags )->HRESULT;
	auto hk_resize( IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags )->HRESULT;

	static bool show_menu = true;
	inline bool m_unloading;
	namespace o {
		inline void* present;
		inline void* resize;
		inline WNDPROC wnd_proc;
	}
}