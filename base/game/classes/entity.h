#pragma once
#include "arma_string.h"
#include "../../utils/utils.h"
#include "../../utils/vector/vector.h"

static uintptr_t get_bone_pos_player_sig = g_utils.signature( "40 53 48 83 EC 20 48 8B 89 ? ? ? ? 48 8B DA E8 ? ? ? ? 48 8B C3 48 83 C4 20 5B C3 CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC E9 ? ? ? ?" );
static uintptr_t get_bone_pos_infected_sig = g_utils.signature( "40 53 48 83 EC 20 48 8B 89 ? ? ? ? 48 8B DA E8 ? ? ? ? 48 8B C3 48 83 C4 20 5B C3 CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC 48 8B 89 ? ? ? ? E9 ? ? ? ? CC CC CC CC 48 8B 89 ? ? ? ?" );


class entity_ai_type
{
public:
	arma_string* get_config_name()
	{
		return *reinterpret_cast< arma_string** >( (uintptr_t)this + 0x0068 );
	}
	arma_string* get_object_name( )
	{
		return *reinterpret_cast< arma_string** >( ( uintptr_t )this + 0x00A0 );
	}
	arma_string* get_clean_name( )
	{
		return *reinterpret_cast< arma_string** >( ( uintptr_t )this + 0x04E0 );
	}
};

class entity_type
{
public:
	inline entity_ai_type* get_type( )
	{
		if( !g_utils.valid_ptr( this ) )
			return 0x0;

		return *reinterpret_cast< entity_ai_type** >( this + 0X90 );
	}
};

class visual_state
{
public:
	vector get_position( )
	{
		return *reinterpret_cast< vector* >( reinterpret_cast< std::uintptr_t >( this ) + 0x2C );
	}
};

class entity
{
public:
	bool is_dead( ) {
		return *reinterpret_cast< bool* >( this + 0x15D );
	}

	float get_health( ) {
		uintptr_t the_class = *reinterpret_cast< uintptr_t* >( this + 0x150 );
		if ( !g_utils.valid_ptr( the_class ) )
			return 100.0f;
			
		return *reinterpret_cast< float* >( the_class + 0x10 );
	}

	int get_network_id( )
	{
		return *reinterpret_cast< int* >( this + 0x634 );
	}

	visual_state* get_visual_state( )
	{
		return *reinterpret_cast< visual_state** >( this + 0x0198 );
	}
	
	entity_type* get_entity_type( )
	{
		return *reinterpret_cast< entity_type** >( this + 0x148 );
	}
};
