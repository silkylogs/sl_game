#include <SDL2/SDL.h>

#include "GameMain.h"

int main( int argc, char** argv ){
	GameMain gs;
	GameMain_ctor(&gs);
	while( GameMain_isGameRunning(&gs) ){
		GameMain_update(&gs);
	}

	GameMain_dtor(&gs);
	return 0;
}

