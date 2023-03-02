#ifndef INPUT_HANDLER_2_HEADER_DEFINED
#define INPUT_HANDLER_2_HEADER_DEFINED

#include <SDL2/SDL.h>

// Prints a warning to stderr in the form
// <filename>:<linenumber>:<functionName>(): <warningLevel>: <moreDetails>
#define WARNING_MACRO(WLEVEL,WSTRING)\
	fprintf(stderr,\
		"%s:%d:%s(): %s: %s\n",\
		__FILE__, __LINE__, __func__,\
		WLEVEL, WSTRING);

// Let command2 be a typedef to a function pointer
// which takes in void and returns a void
typedef void (Command2)(void);

struct InputHandler2 {
	// The buttons supported by the game
	Command2* quitFunctionCallback;
};

// Much preferable to do a `InputHandler2 ih2 = {0};` instead
// Initializes all variables in the InputHandler
void InputHandler2_ctor(InputHandler2* ih2){
	if(!ih2){
		WARNING_MACRO("Warning", "Null argument");
		return;
	}

	// Assign all the callbacks to null
	ih2->quitFunctionCallback = NULL;
}

void InputHandler2_assignCallbackToButton(
	InputHandler2* ih2,
	SDL_Keycode keyCode,
	Command2* button
){
	#define ASSIGN_CMD2_TO_BUTTON( KEYCODE, BUTTON )\
		case KEYCODE: { BUTTON = button; } break;

	switch( keyCode ) {
		ASSIGN_CMD2_TO_BUTTON( SDLK_ESCAPE, ih2->quitFunctionCallback);
		default: /*{ mButtonNull = button; }*/ break;
	}

	#undef ASSIGN_CMD2_TO_BUTTON
}

Command2* InputHandler2_handleInput(InputHandler2* ih2, SDL_Event e){
	// Single press key	
	#define HANDLE_SINGLEPRESS_INPUT( KEYCODE, RETCMD )\
		 case KEYCODE: return RETCMD; break;
	if(e.type==SDL_KEYDOWN){
		switch(e.key.keysym.sym){
			HANDLE_SINGLEPRESS_INPUT(
				SDLK_ESCAPE,
				ih2->quitFunctionCallback
			)
			default: {return NULL;} break;
	}}
	#undef HANDLE_SINGLEPRESS_INPUT

	return NULL;
}

#undef WARNING_MACRO
#endif
