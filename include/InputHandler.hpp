#ifndef INPUT_HANDLER_HEADER_INCLUDED
#define INPUT_HANDLER_HEADER_INCLUDED

#include <iostream>
#include "Command.hpp"
#include "GameObject.hpp"

// All global vars are tests; remove from production code once
// prototyping finishes
class NullCommand : public Command {
	virtual void execute(void){ /*std::cout << "NullCommand::execute() called\n";*/ }
} g_nullCommand;

// Note: To avoid segfaults make sure the Command* pointers actually point to valid data

/*
 * To add a button to the class, do the following:
 * - Create a mButton variable representing a key
 * - Initialize this variable in the constructor
 * - Add a case in handleInput();
 * - Add a case in assignCommandToButton();
 *
 * To make these buttons work dont forget to call assignCommandToButton();
 */
class InputHandler {
	public:
	InputHandler(){
		mButtonEsc  = &g_nullCommand;
		mButtonNull = &g_nullCommand;
		mButtonF12  = &g_nullCommand;
		Command* mButtonW = &g_nullCommand;
		Command* mButtonS = &g_nullCommand;
		Command* mButtonA = &g_nullCommand;
		Command* mButtonD = &g_nullCommand;
		Command* mButtonSpace = &g_nullCommand;
	}

	// Note: Add SDL_KeyboardEvent to allow keydown events
	Command* handleInput( SDL_Event e ){
		Command* retCmd = mButtonNull;
	
		// Single press key	
		#define HANDLE_SINGLEPRESS_INPUT( KEYCODE, RETCMD ) case KEYCODE: return RETCMD; break;
		if( e.type == SDL_KEYDOWN ){
			switch( e.key.keysym.sym ){
				HANDLE_SINGLEPRESS_INPUT( SDLK_ESCAPE, mButtonEsc )
				HANDLE_SINGLEPRESS_INPUT( SDLK_F12, mButtonF12 )
				default: { retCmd = mButtonNull; } break;
		}}
		#undef HANDLE_SINGLEPRESS_INPUT

		// Continous response keys
		SDL_PumpEvents();
		const Uint8* sdlKeyState = SDL_GetKeyboardState(NULL);

		#define HANDLE_CONTINIOUS_INPUT( KEYSTATE_ARRAY, SCANCODE, BUTTON ) if(KEYSTATE_ARRAY[SCANCODE])return BUTTON;
		HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_W, mButtonW );
		HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_S, mButtonS );
		HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_A, mButtonA );
		HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_D, mButtonD );
		HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_SPACE, mButtonSpace );
		#undef HANDLE_CONTINIOUS_INPUT		

		return retCmd;
	}

	// Assigns a SDLK_Keycode to one of the private buttons
	void assignCommandToButton( SDL_Keycode keyCode, Command* cmd ){
		#define ASSIGN_CMD_TO_BUTTON( KEYCODE, BUTTON ) case KEYCODE: { BUTTON = cmd; } break;

		switch( keyCode ) {
			ASSIGN_CMD_TO_BUTTON( SDLK_ESCAPE, mButtonEsc )
			ASSIGN_CMD_TO_BUTTON( SDLK_F12, mButtonF12 )
			ASSIGN_CMD_TO_BUTTON( SDLK_w, mButtonW )
			ASSIGN_CMD_TO_BUTTON( SDLK_s, mButtonS )
			ASSIGN_CMD_TO_BUTTON( SDLK_a, mButtonA )
			ASSIGN_CMD_TO_BUTTON( SDLK_d, mButtonD )
			ASSIGN_CMD_TO_BUTTON( SDLK_SPACE, mButtonSpace )
			default: { mButtonNull = cmd; } break;
		}

		#undef ASSIGN_CMD_TO_BUTTON
	}

	// The buttons supported by the game
	private:
	Command* mButtonEsc;
	Command* mButtonF12;
	Command* mButtonW;
	Command* mButtonS;
	Command* mButtonA;
	Command* mButtonD;
	Command* mButtonSpace;
	Command* mButtonNull;
};

#endif
