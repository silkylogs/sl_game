#include <iostream>
#include <SDL2/SDL.h>

#include "GameMain.hpp"

int main( void ){
	GameMain gs;
	GameMain_init(&gs);
	while( gs.isGameRunning() ){
		gs.update();
	}

	return 0;
}

