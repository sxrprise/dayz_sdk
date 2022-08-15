#pragma once
#include "entity.h"

class player : public entity
{
public:
	vector get_bone_pos( int index )
	{
		vector out( 0, 0, 0 );
		if( !g_utils.valid_ptr( this ) )
			return out;

		typedef void* ( __thiscall* fn_get_bone_pos )( entity* entity, vector* out, unsigned int index );
		static const fn_get_bone_pos get_bone_pos = reinterpret_cast < fn_get_bone_pos >( get_bone_pos_player_sig );

		get_bone_pos( this, &out, index );
		return out;
	}

	bool is_unconcscous( ) {
		return *reinterpret_cast< bool* >( this + 0x35AC );
	}
};