#ifndef GAMEWINDOW_HEADER_INCLUDED
#define GAMEWINDOW_HEADER_INCLUDED

#include <SDL2/SDL.h>
#include <stdbool.h>

// Prints a warning to stderr in the form
// <filename>:<linenumber>:<functionName>(): <warningLevel>: <moreDetails>
#define WARNING_MACRO(WLEVEL,WSTRING)\
	fprintf(stderr,\
		"%s:%d:%s(): %s: %s\n",\
		__FILE__, __LINE__, __func__,\
		WLEVEL, WSTRING);

// A more robust wrapper for the game window
typedef struct GameWindow {
	// Window data
	SDL_Window* mWindow;
	
	// Window dimensions
	int mWidth;
	int mHeight;

	// Window focii
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
} GameWindow;

int  GameWindow_getWidth        (GameWindow* gm);
int  GameWindow_getHeight       (GameWindow* gm);
bool GameWindow_isMinimized     (GameWindow* gm);
bool GameWindow_hasMouseFocus   (GameWindow* gm);
bool GameWindow_hasKeyboardFocus(GameWindow* gm);
SDL_Window* GameWindow_getWindow(GameWindow* gm);

void GameWindow_ctor( 
	GameWindow* gameWindow,
	char* windowTitle,
	int wWidth, int wHeight
);

void GameWindow_dtor( GameWindow* gm );

void GameWindow_handleWindowEvents(
	GameWindow *gameWindow,
	SDL_Event e,
	SDL_Renderer* renderer
);

void GameWindow_setFullScreen( GameWindow* gw );

#endif
