#ifndef INPUT_HANDLER_HEADER_INCLUDED
#define INPUT_HANDLER_HEADER_INCLUDED

#include <iostream>
#include "Command.hpp"
#include "GameObject.hpp"

// all global vars are tests; remove from production code once
// prototyping finishes
QuitCommand g_quitCommand;
NullCommand g_nullCommand;

// To avoid segfaults make sure the Command* pointers actually point to valid data

class InputHandler {
	public:

	// Temporariliy assigning commands
	InputHandler(){
		mButtonEsc = &g_quitCommand;
		mButtonNull = &g_nullCommand;
	}

	Command* handleInput( SDL_Event& e ){
		Command* returningCommand = NULL;
		
		switch( e.key.keysym.sym ){
			case SDLK_ESCAPE: returningCommand = mButtonEsc;
			default: returningCommand = mButtonNull;
		}

		return returningCommand;
	}

	void mapInputToCommand(){ std::cerr << "Todo\n"; }

	private:
	Command* mButtonEsc;
	Command* mButtonNull;
};

#endif
