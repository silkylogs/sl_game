#ifndef INPUT_HANDLER_HEADER_INCLUDED
#define INPUT_HANDLER_HEADER_INCLUDED

#include <iostream>
#include "Command.hpp"
#include "GameObject.hpp"

// Note: To avoid segfaults make sure the Command* callbacks actually point to valid data

/* DEPRECATED ADVICE: MODIFY ASAP
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
	//void init(){mButtonEsc=NULL;}

	//Command* handleInput(SDL_Event);


	// The buttons supported by the game
	public:
	Command* mButtonEsc;
	//void (*quitFunctionCallback)(void); //cdcel.org
};

void InputHandler_ctor(InputHandler* ih){
	if(ih)ih->mButtonEsc=NULL;
}

Command* InputHandler_handleInput(InputHandler* ih, SDL_Event e){
	/*
	// Note: Add SDL_KeyboardEvent to allow keydown events
	// Continous response keys
	SDL_PumpEvents();
	const Uint8* sdlKeyState = SDL_GetKeyboardState(NULL);

	#define HANDLE_CONTINIOUS_INPUT( KEYSTATE_ARRAY, SCANCODE, BUTTON ) \
		if(KEYSTATE_ARRAY[SCANCODE])return BUTTON;
	
	HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_W, mButtonW );
	HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_S, mButtonS );
	HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_A, mButtonA );
	HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_D, mButtonD );
	HANDLE_CONTINIOUS_INPUT( sdlKeyState, SDL_SCANCODE_SPACE, mButtonSpace);
	
	#undef HANDLE_CONTINIOUS_INPUT
	*/


	// Single press key	
	#define HANDLE_SINGLEPRESS_INPUT( KEYCODE, RETCMD )\
		 case KEYCODE: return RETCMD; break;
	if(e.type==SDL_KEYDOWN){
		switch(e.key.keysym.sym){
			HANDLE_SINGLEPRESS_INPUT(SDLK_ESCAPE,ih->mButtonEsc)
			default: {return NULL;} break;
	}}
	#undef HANDLE_SINGLEPRESS_INPUT

	return NULL;
}

// Assigns a SDLK_Keycode to one of the private buttons
void InputHandler_assignCommandToButton(
	InputHandler* ih,
	SDL_Keycode keyCode,
	Command* button
){
	#define ASSIGN_CMD_TO_BUTTON( KEYCODE, BUTTON )\
		case KEYCODE: { ih->BUTTON = button; } break;

	switch( keyCode ) {
		ASSIGN_CMD_TO_BUTTON( SDLK_ESCAPE, mButtonEsc )
		default: /*{ mButtonNull = button; }*/ break;
	}

	#undef ASSIGN_CMD_TO_BUTTON
}

#endif
