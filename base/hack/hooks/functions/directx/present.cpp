#include "../../hooks.h"
#include "../../../features/visuals.h"
#include "../../../../utils/smallest_pixel.h"

ID3D11Device* device = nullptr;
ID3D11DeviceContext* immediate_context = nullptr;
ID3D11RenderTargetView* render_target_view = nullptr;

extern LRESULT ImGui_ImplWin32_WndProcHandler( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );

ImGuiWindow& begin_scene( ) {
	ImGui_ImplDX11_NewFrame( );
	ImGui_ImplWin32_NewFrame( );
	ImGui::NewFrame( );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowBorderSize, 0 );
	ImGui::PushStyleVar( ImGuiStyleVar_WindowPadding, ImVec2( 0, 0 ) );
	ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( 0, 0, 0, 0 ) );
	ImGui::Begin( "##scene", nullptr, ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar );

	auto& io = ImGui::GetIO( );

	ImGui::SetWindowPos( ImVec2( 0, 0 ), ImGuiCond_Always );
	ImGui::SetWindowSize( ImVec2( io.DisplaySize.x, io.DisplaySize.y ), ImGuiCond_Always );

	return *ImGui::GetCurrentWindow( );
}

void end_scene( ImGuiWindow& window ) {
	window.DrawList->PushClipRectFullScreen( );
	ImGui::End( );
	ImGui::PopStyleColor( );
	ImGui::PopStyleVar( 2 );
	ImGui::PushStyleColor( ImGuiCol_WindowBg, ImVec4( 0.17f, 0.18f, 0.2f, 1.0f ) );

	if( hooks::show_menu )
	{
		ImGui::GetStyle( ).WindowPadding = { 0, 0 };
		ImGui::GetStyle( ).WindowMinSize = { 1, 1 };
		ImGui::GetStyle( ).WindowBorderSize = 0;
		ImGui::GetStyle( ).PopupBorderSize = 1;
		ImGui::GetStyle( ).PopupRounding = 4;
		ImGui::GetStyle( ).WindowRounding = 8;
		ImGui::GetStyle( ).GrabMinSize = 1;
		ImGui::GetStyle( ).ItemSpacing = { 5, 10 };
		ImGui::GetStyle( ).ColorButtonPosition = ImGuiDir_Right;

		ImGui::GetStyle( ).Colors[ ImGuiCol_WindowBg ] = ImColor{ 18, 18, 18, 0 };
		ImGui::GetStyle( ).Colors[ ImGuiCol_PopupBg ] = ImColor{ 17, 17, 17 };
		ImGui::GetStyle( ).Colors[ ImGuiCol_Border ] = ImColor{ 33, 33, 33 };
		ImGui::GetStyle( ).Colors[ ImGuiCol_Text ] = ImColor{ 255, 255, 255 };
		ImGui::GetStyle( ).Colors[ ImGuiCol_ScrollbarBg ] = ImColor{ 119, 119, 119, 0 };

		ImGui::GetStyle( ).Colors[ ImGuiCol_Header ] = ImColor{ 35, 42, 51 };
		ImGui::GetStyle( ).Colors[ ImGuiCol_HeaderActive ] = ImColor{ 35, 42, 51 };
		ImGui::GetStyle( ).Colors[ ImGuiCol_HeaderHovered ] = ImColor{ 35, 42, 51 };

		auto flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;

		static auto selected_tab = 0;

		ImGui::Begin( "Interface", nullptr, flags );
		{
			auto draw = ImGui::GetWindowDrawList( );
			auto pos = ImGui::GetWindowPos( );

			ImGui::SetWindowSize( { 425, 350 } );

			static float sidebar_x = 32;

			draw->AddRectFilled( pos, pos + ImVec2( 425, 350 ), ImColor( 17, 17, 17 ), 8 );

			//    auto easingFunction = getEasingFunction(EaseInExpo);
		}
		ImGui::End( );
	}
		//menu::draw( );

	ImGui::PopStyleColor( );
	ImGui::Render( );

	ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData( ) );
}

LRESULT __stdcall hk_wnd_proc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) {

	if( hooks::m_unloading )
		return CallWindowProcW( hooks::o::wnd_proc, hWnd, msg, wParam, lParam );

	if( msg == WM_KEYUP && ( wParam == VK_HOME ) ) {
		hooks::show_menu = !hooks::show_menu;
		ImGui::GetIO( ).MouseDrawCursor = hooks::show_menu;
	}

	ImGui_ImplWin32_WndProcHandler( hWnd, msg, wParam, lParam );

	return CallWindowProcW( hooks::o::wnd_proc, hWnd, msg, wParam, lParam );
}

HRESULT hooks::hk_present( IDXGISwapChain* swapChain, UINT syncInterval, UINT flags ) {

	if( hooks::m_unloading ) 
		return reinterpret_cast< decltype( &hk_present ) >( hooks::o::present )( swapChain, syncInterval, flags );
	
	if( !device )
	{
		swapChain->GetDevice( __uuidof( device ), reinterpret_cast< PVOID* >( &device ) );
		device->GetImmediateContext( &immediate_context );

		ID3D11Texture2D* renderTarget = nullptr;
		swapChain->GetBuffer( 0, __uuidof( renderTarget ), reinterpret_cast< PVOID* >( &renderTarget ) );
		device->CreateRenderTargetView( renderTarget, nullptr, &render_target_view );
		renderTarget->Release( );

		DXGI_SWAP_CHAIN_DESC desc;
		swapChain->GetDesc( &desc );

		ImGui::CreateContext( );
		auto& io = ImGui::GetIO( );
		if( !g_renderer.smallest_pixel )
			g_renderer.smallest_pixel = io.Fonts->AddFontFromMemoryTTF( &smallest_pixel_font, sizeof( smallest_pixel_font ), 10.f );
	
		if( !g_renderer.verdana )
			g_renderer.verdana = io.Fonts->AddFontFromFileTTF( "C:\\Windows\\Fonts\\verdana.ttf", 12 );
		
		ImFontConfig icons_config;
		icons_config.MergeMode = true;
		icons_config.PixelSnapH = true;
		
		auto hwnd = FindWindow( _( "DayZ" ), nullptr );
		hooks::o::wnd_proc = reinterpret_cast< WNDPROC >( SetWindowLongPtr( hwnd, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hk_wnd_proc ) ) );

		ImGui_ImplWin32_Init( hwnd );
		ImGui_ImplDX11_Init( device, immediate_context );
		//ImGui_ImplDX11_CreateDeviceObjects( );
	}

	immediate_context->OMSetRenderTargets( 1, &render_target_view, nullptr );

	auto& window = begin_scene( );

	g_visuals.draw_entity_esp( );
	//features::aimbot.find_aimbot_target( );
	//features::aimbot.run( );
	//features::aimbot.teleport_to_local( );

	end_scene( window );

	return reinterpret_cast< decltype( &hk_present ) >( hooks::o::present )( swapChain, syncInterval, flags );
}

HRESULT hooks::hk_resize( IDXGISwapChain* swapChain, UINT bufferCount, UINT width, UINT height, DXGI_FORMAT newFormat, UINT swapChainFlags ) {
	ImGui_ImplDX11_Shutdown( );
	ImGui::DestroyContext( );
	render_target_view->Release( );
	immediate_context->Release( );
	device->Release( );
	device = nullptr;

	return reinterpret_cast< decltype( &hk_resize ) >( hooks::o::resize )( swapChain, bufferCount, width, height, newFormat, swapChainFlags );
}