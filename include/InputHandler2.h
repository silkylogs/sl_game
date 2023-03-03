#ifndef INPUT_HANDLER_2_HEADER_DEFINED
#define INPUT_HANDLER_2_HEADER_DEFINED

#include <SDL2/SDL.h>

// Let command2 be a typedef to a function pointer
// which takes in a void* and returns a void
typedef void (Command2)(void*);

// Contains the buttons supported by the game
typedef struct InputHandler2 {
	Command2* bEsc;
} InputHandler2;

// Much preferable to do a `InputHandler2 ih2 = {0};` instead
// Initializes all variables in the InputHandler
void InputHandler2_ctor(InputHandler2* ih2);

// Maps a user defined function to one of the internal buttons
void InputHandler2_assignCallbackToButton(InputHandler2*,SDL_Keycode,Command2*);

// Returns the function pointer corresponding to the action
// present in SDL_Event
Command2* InputHandler2_handleInput(InputHandler2*, SDL_Event);

#endif
