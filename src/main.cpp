#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "Command.hpp"
#include "GameWindow.hpp"
#include "GameState.hpp"

bool g_gameRunning = true;

// todo: make the new input manager quits the game normally
// without resorting to cmd + q

int main( void ){
	GameState gs;
	while( gs.isGameRunning() ){
		gs.update();
	}

	return 0;
}

