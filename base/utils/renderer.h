#pragma once
#include "../hack/hooks/hooks.h"

class renderer
{
public:
	// Oh Allah, help me make correct choices

	void text( const ImVec2 v2_pos, std::string str_text, ImVec4 v4_col )
	{
		const char* text = str_text.c_str( );

		ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x - 1, v2_pos.y - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );
		ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x + 1, v2_pos.y - 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );
		ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x - 1, v2_pos.y + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );
		ImGui::GetWindowDrawList( )->AddText( ImVec2( v2_pos.x + 1, v2_pos.y + 1 ), ImGui::GetColorU32( ImVec4( 0, 0, 0, 255 * v4_col.w ) ), text );

		ImGui::GetWindowDrawList( ) ->AddText( v2_pos, ImGui::GetColorU32( v4_col ), text );
	}

	void rect( ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col )
	{
		ImGui::GetWindowDrawList( )->AddRect( ImVec2( v2_pos.x - 1, v2_pos.y - 1 ), ImVec2( v2_pos.x + v2_size.x + 1, v2_pos.y + v2_size.y + 1 ), ImColor( 0, 0, 0, 255 ), 0.0f, 15, 1 );
		ImGui::GetWindowDrawList( )->AddRect( ImVec2( v2_pos.x, v2_pos.y ), ImVec2( v2_pos.x + v2_size.x, v2_pos.y + v2_size.y ), ImGui::GetColorU32( v4_col ), 0.0f, 15, 1 );
		ImGui::GetWindowDrawList( )->AddRect( ImVec2( v2_pos.x + 1, v2_pos.y + 1 ), ImVec2( v2_pos.x + v2_size.x - 1, v2_pos.y + v2_size.y - 1 ), ImColor( 0, 0, 0, 255 ), 0.0f, 15, 1 );
	}

	void line( ImVec2 start, ImVec2 end, ImVec4 v4_col ) {
		ImGui::GetWindowDrawList( )->AddLine( start, end, ImGui::GetColorU32( v4_col ), 1.0f );
	}

	template <class T>
	void box( T x1, T y1, T x2, T y2, ImColor color, float thickness = 1.f, float rounding = 0.f, bool outline = false ) {

		ImGui::GetWindowDrawList( )->AddRect( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImColor( color ), rounding);
	}

	template <class T>
	void filled_box( T x1, T y1, T x2, T y2, ImColor color, float thickness = 1.f, float rounding = 0.f, bool outline = false ) {

		ImGui::GetWindowDrawList( )->AddRectFilled( ImVec2( x1, y1 ), ImVec2( x2, y2 ), ImColor( color ), rounding );
	}

	void gradient(ImVec2 v2_pos, ImVec2 v2_size, ImVec4 v4_col, ImColor v4_col2 )
	{
		const ImRect rect_bb( v2_pos, ImVec2( v2_pos.x + v2_size.x, v2_pos.y + v2_size.y ) );

		auto gradient = ImGui::GetColorU32( v4_col ) - v4_col2;
		ImGui::GetWindowDrawList( )->AddRectFilledMultiColor( rect_bb.Min, rect_bb.Max, ImGui::GetColorU32( v4_col ), ImGui::GetColorU32( v4_col ), gradient, gradient );
	}

private:
	//ImGuiWindow* window = ImGui::GetCurrentWindow( );

public:
	ImFont* smallest_pixel;
	ImFont* verdana;
};

extern renderer g_renderer;