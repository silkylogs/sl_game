#ifndef INPUT_HANDLER_HEADER_INCLUDED
#define INPUT_HANDLER_HEADER_INCLUDED

#include <iostream>
#include "Command.hpp"
#include "GameObject.hpp"

// All global vars are tests; remove from production code once
// prototyping finishes
class NullCommand : public Command {
	virtual void execute(void){ /*std::cout << "NullCommand.execute() called\n";*/ }
} g_nullCommand;

// Note: To avoid segfaults make sure the Command* pointers actually point to valid data

/*
 * To add a button to the class, do the following:
 * - Create a mButton variable representing a key
 * - Initialize this variable in the constructor
 * - Add a case in handleInput();
 * - Add a case in assignCommandToButton();
 * - Do not forget to `break;`
 *
 * To make these buttons work dont forget to call assignCommandToButton();
 */
class InputHandler {
	public:
	InputHandler(){
		mButtonEsc  = &g_nullCommand;
		mButtonNull = &g_nullCommand;
		mButtonF12  = &g_nullCommand;
	}

	Command* handleInput( SDL_Keycode keyCode ){
		Command* retCmd = mButtonNull;
		
		switch( keyCode ){
			case SDLK_ESCAPE: 
			retCmd = mButtonEsc;
			break;

			case SDLK_F12:
			retCmd = mButtonF12;
			break;			

			default:
			retCmd = mButtonNull;
			break;
		}

		return retCmd;
	}

	// Assigns a SDLK_Keycode to one of the private buttons
	void assignCommandToButton( SDL_Keycode keyCode, Command* cmd ){
		switch( keyCode ) {
			case SDLK_ESCAPE:
			mButtonEsc = cmd;
			break;

			case SDLK_F12:
			mButtonF12 = cmd;
			break;

			default:
			mButtonNull = cmd;
			break;
		}
	}

	// The buttons supported by the game
	private:
	Command* mButtonEsc;
	Command* mButtonF12;
	Command* mButtonNull;
};

#endif
