#pragma once
#include "classes/game.h"
#include "classes/dayz_player.h"
#include "classes/dayz_infected.h"
#include "classes/dayz_item.h"

class entities
{
public:
	inline std::vector<infected*> get_living( )
	{
		std::vector<infected*> entities;

		entity* localplayer = g_game.get_local( );
		if( !g_utils.valid_ptr( localplayer ) )
			return entities;

		world* world = g_game.get_world( );
		if( !g_utils.valid_ptr( world ) )
			return entities;

		for( int i = 0; i < world->get_slow_table_count( ); i++ )
		{
			int check = *reinterpret_cast< int* >( world->get_slow_table( ) + ( i * 0x18 ) );
			if( check != 1 ) continue;

			infected* zombies = *reinterpret_cast< infected** >( world->get_slow_table( ) + ( ( i * 0x18 ) + 0x8 ) );
			if( !zombies ) continue;

			entity_type* entity_type = zombies->get_entity_type( );
			if( !g_utils.valid_ptr( entity_type ) ) continue;
			entity_ai_type* entity_ai_type = entity_type->get_type( );
			if( !entity_ai_type ) continue;
			arma_string* object_name = entity_ai_type->get_object_name( );
			if( !g_utils.valid_ptr( ( void* )object_name ) )
				continue;

			if( strstr( object_name->get_str( ).c_str( ), "dayzinfected" ) || strstr( object_name->get_str( ).c_str( ), "dayzplayer" ) )
			{
				// push player to vector
				entities.push_back( zombies );
			}
		}

		for( int i = 0; i < world->get_near_table_count( ); i++ )
		{
			infected* zombies = *reinterpret_cast< infected** >( world->get_near_table( ) + ( i * 0x8 ) );
			if( !zombies ) continue;

			entity_type* entity_type = zombies->get_entity_type( );
			if( !g_utils.valid_ptr( entity_type ) ) continue;
			entity_ai_type* entity_ai_type = entity_type->get_type( );
			if( !entity_ai_type ) continue;
			arma_string* object_name = entity_ai_type->get_object_name( );
			if( !g_utils.valid_ptr( ( void* )object_name ) )
				continue;

			if( strstr( object_name->get_str( ).c_str( ), "dayzinfected" ) || strstr( object_name->get_str( ).c_str( ), "dayzplayer" ) )
			{
				// push player to vector
				entities.push_back( zombies );
			}
		}

		for( int i = 0; i < world->get_far_table_count( ); i++ )
		{
			// loop through the table

			if( !world->get_far_table( ) ) continue;

			infected* zombies = *reinterpret_cast< infected** >( world->get_far_table( ) + ( i * 0x8 ) );
			if( !zombies ) continue;

			entity_type* entity_type = zombies->get_entity_type( );
			if( !g_utils.valid_ptr( entity_type ) ) continue;
			entity_ai_type* entity_ai_type = entity_type->get_type( );
			if( !entity_ai_type ) continue;
			arma_string* object_name = entity_ai_type->get_object_name( );
			if( !g_utils.valid_ptr( ( void* )object_name ) )
				continue;

			if( strstr( object_name->get_str( ).c_str( ), "dayzinfected" ) || strstr( object_name->get_str( ).c_str( ), "dayzplayer" ) )
			{
				// push player to vector
				entities.push_back( zombies );
			}

		}
		return entities;
	}

	inline std::vector<item*> get_items( )
	{
		std::vector<item*> entities;

		entity* local_player = g_game.get_local( );
		if( !g_utils.valid_ptr( local_player ) )
			return entities;

		world* world = g_game.get_world( );
		if( !g_utils.valid_ptr( world ) )
			return entities;

		for( int i = 0; i < world->get_item_table_count( ); i++ )
		{
			int check = *reinterpret_cast< int* >( world->get_item_table( ) + ( i * 0x18 ) );
			if( check != 1 ) continue;

			item* items = *reinterpret_cast< item** >( world->get_item_table( ) + ( ( i * 0x18 ) + 0x8 ) );
			if( !items ) continue;

			entity_type* entity_type = items->get_entity_type( );
			if( !g_utils.valid_ptr( entity_type ) ) continue;
			entity_ai_type* entity_ai_type = entity_type->get_type( );
			if( !entity_ai_type ) continue;
			arma_string* object_name = entity_ai_type->get_object_name( );
			if( !g_utils.valid_ptr( ( void* )object_name ) )
				continue;

			// push player to vector
			entities.push_back( items );
		}
		return entities;
	}

};

entities g_entities;

