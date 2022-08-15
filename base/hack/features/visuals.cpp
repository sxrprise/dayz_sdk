#include "visuals.h"
#include "../../game/entities.h"
#include <algorithm>
// i dont wanna hear shit for this idc 
renderer g_renderer;

visuals g_visuals;

void visuals::draw_entity_esp( )
{
	entity* local_player = g_game.get_local( );
	if( !g_utils.valid_ptr( local_player ) )
		return;

	world* world = g_game.get_world( );
	if( !g_utils.valid_ptr( world ) )
		return;

	world->get_dx_engine( )->set_fov( 20.f );

	auto watermark_string = "dayz base";
	auto watermark_size = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, watermark_string );
	
	g_renderer.box<int>(0, 0, watermark_size.x + 11, 14, ImVec4( 0.23, 0.23, 0.23, 1 ), 1.f, true );
	g_renderer.rect( ImVec2( 0, 0 ), ImVec2( watermark_size.x + 10, 14 ), ImVec4( 0.45, 0.45, 0.45, 1 ) );
	g_renderer.text( ImVec2( 5, 0 ), "dayz base", ImVec4( 1, 1, 1, 1 ) );
	
	//please allah forgive of me for this you are our savior and only hope. 
	std::vector<infected*> living = g_entities.get_living( );
	for( int i = 0; i < living.size( ); i++ )
	{
		// get player
		infected* entity = living[ i ];
		if( !entity ) continue;

		if( entity == local_player )
			continue;

		if( entity->is_dead( ) )
			continue;
		
		vector entity_position = entity->get_visual_state( )->get_position( );
		
		if( entity_position.is_zero( ) )
			continue;
		
		camera* camera = world->get_camera( );
		if( !g_utils.valid_ptr( camera ) )
			continue;

		vector screen_pos;
		if( !camera->screen_transform( entity_position, screen_pos ) )
			continue;

		vector head_pos{ };
		ImColor color;
		if( entity->get_entity_type( )->get_type( )->get_object_name( )->get_str( ) == "dayzplayer" )
		{
			head_pos = ( ( player* )entity )->get_bone_pos( 17 );
			color = ImColor( 28, 255, 20);
		}
		else if( entity->get_entity_type( )->get_type( )->get_object_name( )->get_str( ) == "dayzinfected" )
		{
			head_pos = ( ( infected* )entity )->get_bone_pos( 17 );
			color = ImColor( 255, 59, 20 );
		}
		
		/* oh allah you shall be ashamed of me please forgive me once again : (*/
		vector screen_head_pos;
		if( !camera->screen_transform( head_pos + .2, screen_head_pos ) )
			continue;
		
		// o allah will you forgive me of my sins and my sins will be forgiven.
		auto box_h = fabs( screen_head_pos.y - screen_pos.y );
		auto box_w = box_h / 1.65f;
		
		auto left = screen_pos.x - box_w * 0.5f;
		auto right = left + box_w;
		auto bottom = screen_pos.y;
		auto top = screen_head_pos.y;
		
		auto local_pos = local_player->get_visual_state( )->get_position( );
		auto zmbi_pos = entity->get_visual_state( )->get_position( );

		auto distance = static_cast< int >( local_pos.dist_to( zmbi_pos ) );
		
		static int alpha = 255;
		alpha += distance > 300 ? -1 : 25;
	
		std::clamp( alpha, 0, 255 );
		
		// name esp
		{
			auto name = entity->get_entity_type( )->get_type( )->get_clean_name( )->get_str( );
		
			auto sz = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, name.c_str( ) );
		
			ImGui::PushFont( g_renderer.smallest_pixel );
			g_renderer.text( ImVec2( ( left + box_w / 2 ) - sz.x / 2, top - sz.y - 1 ), name, ImColor( 255, 255, 255, alpha ) );
			ImGui::PopFont( );
			
		}
		// distance esp
		{	
			auto dist_str = std::string( std::to_string( distance ) + "m" );
		
			auto dist_sz = g_renderer.smallest_pixel->CalcTextSizeA( 10.f, FLT_MAX, 0.0f, dist_str.c_str( ) );
			
			ImGui::PushFont( g_renderer.smallest_pixel );
			g_renderer.text( ImVec2( ( left + box_w / 2 ) - dist_sz.x / 2, top + box_h + 1.f ), dist_str, ImColor(255,255,255, alpha) );
			ImGui::PopFont( );
		}
		// healthbar
		{
			int health = entity->get_health( );
			float health_box_h = ( float )fabs( bottom - top );
			float off = 6;
			
			int height = ( health_box_h * health ) / 100;
			
			int green = int( health * 2.55f );
			int red = 255 - green;
			
			int x = left - off;
			int y = bottom;
			int w = 4;
			
			g_renderer.filled_box<int>( x, y, x + w, y + health_box_h, ImColor( 0, 0, 0, 255 ), 1, 1 );
			g_renderer.filled_box<int>( x + 1, y + 1, x + w - 1, y + height - 2, ImColor( red, green, 0, 255 ), 1.f, true );
		}
		// box :skull:
		{
			g_renderer.box<int>( left - 1, top - 1, right + 1, bottom + 1, ImColor( 0, 0, 0, alpha ), 1, 0, 1 );
			g_renderer.box<int>( left + 1, top + 1, right - 1, bottom - 1, ImColor( 0, 0, 0, alpha ), 1, 0, 1 );
			g_renderer.box<int>( left, top, right, bottom, ImColor(color.Value.x, color.Value.y, color.Value.z, (float)alpha ), 1, 0, 1 );
		
		}
	}
}
