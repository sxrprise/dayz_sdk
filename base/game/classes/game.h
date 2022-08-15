#pragma once
#include "entity.h"
#include "camera.h"
#include <dxgi.h>

static uintptr_t get_local_sig;
static uintptr_t get_world_sig;

class engine_dx
{
public:
	void set_fov( float fov )
	{
		// FOV
		*reinterpret_cast< float* >( this + 0x70 ) = fov / 10.f;
		// Aspect Ratio
		*reinterpret_cast< float* >( this + 0x6C ) = fov / 10.f;
	}	
};

class world
{
public:
	uintptr_t get_far_table( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< uintptr_t* >( this + 0x1000 );
	}
	
	int get_far_table_count( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< int* >( this + 0x1008 );
	}

	uintptr_t get_near_table( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< uintptr_t* >( this + 0x0EB8 );
	}
	
	int get_near_table_count( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< int* >( this + 0x0EC0 );
	}
		
	uintptr_t get_slow_table( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< uintptr_t* >( this + 0x1F68 );
	}
	
	int get_slow_table_count( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< int32_t* >( this + 0x1F70 );
	}

	uintptr_t get_item_table( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< uintptr_t* >( this + 0x1FB8 );
	}
	
	int get_item_table_count( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return  *reinterpret_cast< uintptr_t* >( this + 0x1FC0 );
	}

	camera* get_camera( ) 
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return *reinterpret_cast< camera** >( this + 0x1B8 );
		
	}
	engine_dx* get_dx_engine( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;
		return *reinterpret_cast< engine_dx** >( this + 0x28 );
	}
};

class game
{
public:
	world* get_world( )
	{
		if( !get_world_sig )
			get_world_sig = g_utils.signature( "48 8B 05 ? ? ? ? C3 CC CC CC CC CC CC CC CC 48 89 5C 24 ? 57 48 83 EC 20 48 8B FA" );
		typedef void* ( __stdcall* fn_get_world )( );
		static const fn_get_world get_world = reinterpret_cast < fn_get_world >( get_world_sig );
	
		return reinterpret_cast< world* >( get_world( ) );
	}
	
	entity* get_local( )
	{
		if( !get_local_sig )
			get_local_sig = g_utils.signature( "48 83 EC 28 48 8B 0D ? ? ? ? 48 85 C9 74 11 E8 ? ? ? ?" );

		typedef void* ( __stdcall* fn_get_local_player )( );
		static const fn_get_local_player get_local_player = reinterpret_cast < fn_get_local_player >( get_local_sig );
		
		return reinterpret_cast< entity* >( get_local_player( ) );
	}
}; 

game g_game;