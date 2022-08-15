#define NOMINMAX
#include <Windows.h>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include "hack/hooks/hooks.h"
#include "utils/console/console.h"
#include "utils/utils.h"
#include "game/classes/dayz_infected.h"

/* oh mah gawww boy got a glockk */

/* OH HE CANT READDD MY POKERR FACEEE OOOOOH */

/* papapapappapapa pokerrr faceeeeeeeeeeeeeeeee */

__declspec( noreturn ) void free_memory( void* base, SIZE_T size ) {
	auto* pmemset = memset;
	auto* virtualfree = VirtualFree;
	auto* exitthread = ExitThread;

	pmemset( base, 0, size );
	virtualfree( base, 0, MEM_RELEASE );
	exitthread( WN_SUCCESS );
}

void on_unload( HINSTANCE mod ) {
	g_console.release( );
	hooks::detach( );

	FreeLibraryAndExitThread( mod, EXIT_SUCCESS );

	auto* exit_dll = reinterpret_cast< decltype( free_memory )* >( VirtualAlloc( nullptr, 0x100, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE ) );
	memcpy( exit_dll, free_memory, 0x100 );
	exit_dll( mod, sizeof( mod ) );
}

void on_attach( HINSTANCE mod ) {
#ifdef _DEBUG
	g_console.initialize( _( "base" ) );
#endif

	hooks::attach( );
	
	// wait for unload key 
	while( !( GetAsyncKeyState( VK_END ) & 0x8000 ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 500 ) );

	on_unload( mod );
}

BOOL APIENTRY DllMain( HMODULE module_handle, DWORD call_reason, LPVOID reserved ) {
	switch( call_reason ) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls( module_handle );
		CreateThread( 0, 0, reinterpret_cast< LPTHREAD_START_ROUTINE >( on_attach ), reinterpret_cast< HMODULE >( module_handle ), 0, 0 );
		return TRUE;

	case DLL_PROCESS_DETACH:
		//on_unload();
		return TRUE;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		return FALSE;
	}
}