#include "InputHandler2.h"
// Prints a warning to stderr in the form
// <filename>:<linenumber>:<functionName>(): <warningLevel>: <moreDetails>
#define WARNING_MACRO(WLEVEL,WSTRING)\
	fprintf(stderr,\
		"%s:%d:%s(): %s: %s\n",\
		__FILE__, __LINE__, __func__,\
		WLEVEL, WSTRING);

void InputHandler2_ctor(InputHandler2* ih2){
	if(!ih2){
		WARNING_MACRO("Warning", "Null argument");
		return;
	}

	// Assign all the callbacks to null
	ih2->bEsc = NULL;
}

void InputHandler2_assignCallbackToButton(
	InputHandler2* ih2,
	SDL_Keycode keyCode,
	Command2* buttonCallback
){
	if(!ih2){
		WARNING_MACRO("Warning", "Null argument");
		return;
	}

	#define ASSIGN_CMD2_TO_BUTTON(KEYCODE, BUTTON)\
		case KEYCODE: { BUTTON = buttonCallback; } break;

	switch( keyCode ) {
		ASSIGN_CMD2_TO_BUTTON(SDLK_ESCAPE, ih2->bEsc);
		printf("b\n");
		default: /*{ mButtonNull = button; }*/ break;
	}

	#undef ASSIGN_CMD2_TO_BUTTON
}

Command2* InputHandler2_handleInput(InputHandler2* ih2, SDL_Event e){
	if(!ih2){
		WARNING_MACRO("Warning", "Null argument");
		return NULL;
	}

	// Single press key
	#define SELECT_RET_COMMAND( KEYCODE, RETCMD )\
		 case KEYCODE: return RETCMD; break;

	if(e.type==SDL_KEYDOWN){
		switch(e.key.keysym.sym){
			SELECT_RET_COMMAND(SDLK_ESCAPE, ih2->bEsc)
			default: { return NULL; } break;
	}}

	#undef SELECT_RET_COMMAND

	return NULL;
}

#undef WARNING_MACRO
