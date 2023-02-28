#include <iostream>
#include <SDL2/SDL.h>

#include "GameMain.hpp"

int main( void ){
	GameMain gs;
	GameMain_ctor(&gs);
	while( GameMain_isGameRunning(&gs) ){
		GameMain_update(&gs);
	}

	GameMain_dtor(&gs);
	return 0;
}

