#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "Command.hpp"
#include "GameWindow.hpp"
#include "GameMain.hpp"

int main( void ){
	GameMain gs;
	while( gs.isGameRunning() ){
		gs.update();
	}

	return 0;
}

