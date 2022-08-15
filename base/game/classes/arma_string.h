#pragma once
#include <codecvt>

class arma_string
{
public:
	std::string get_str( )
	{
		auto size = *reinterpret_cast< uint32_t* >(
			reinterpret_cast< uintptr_t >( this )
			+ 0x8 );

		if( size == 0 )
			return "";

		return reinterpret_cast< char* >(
			reinterpret_cast< uintptr_t >( this )
			+ 0x10 );
	}

	void set_str( const std::string set )
	{
		auto size = *reinterpret_cast< uint32_t* >(
			reinterpret_cast< uintptr_t >( this )
			+ 0x8 );

		if( size == 0 )
			return;

		memcpy(
			reinterpret_cast< void* >(
				reinterpret_cast< uintptr_t >( this )
				+ 0x10 ),
			set.data( ),
			set.size( ) );
	}

};