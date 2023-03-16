#include "GameWindow.h"

int  GameWindow_getWidth        (GameWindow* gm) { return gm->mWidth; }
int  GameWindow_getHeight       (GameWindow* gm) { return gm->mHeight; }
bool GameWindow_isMinimized     (GameWindow* gm) { return gm->mMinimized; }
bool GameWindow_hasMouseFocus   (GameWindow* gm) { return gm->mMouseFocus; }
bool GameWindow_hasKeyboardFocus(GameWindow* gm) { return gm->mKeyboardFocus; }
SDL_Window* GameWindow_getWindow(GameWindow* gm) { return gm->mWindow; }

void GameWindow_ctor( 
	GameWindow* gameWindow,
	const char* windowTitle,
	int wWidth, int wHeight
){
	
	if(!gameWindow){ 
		WARNING_MACRO("Warning", "Null argument");
		return;
	}

	gameWindow->mMouseFocus    = false ;
	gameWindow->mKeyboardFocus = false ;
	gameWindow->mFullScreen    = false ;
	gameWindow->mMinimized     = false ;
	gameWindow->mWindow        = NULL  ;

	// Validate inputted width and height
	gameWindow->mHeight = wHeight;
	gameWindow->mWidth  = wWidth;
	if( gameWindow->mWidth <= 0 ) {
		fprintf(stderr,
			"%s:%d:%s():"
			"Argument has an invalid window width. (x == %d)"
			"Continuting with a safer width...\n",
			__FILE__, __LINE__, __func__, gameWindow->mWidth
		);
		gameWindow->mWidth = 800;
	}
	if( gameWindow->mHeight <= 0 ) {
		fprintf(stderr,
			"%s:%d:%s():"
			"Argument has an invalid window height. (x == %d)"
			"Continuting with a safer height...\n",
			__FILE__, __LINE__, __func__, gameWindow->mHeight
		);
		gameWindow->mHeight = 600;
	}
	
	if( windowTitle ) { 
		gameWindow->mWindow = SDL_CreateWindow(
			windowTitle,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			gameWindow->mWidth, gameWindow->mHeight,
			SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE
		);
	}
	else{
		gameWindow->mWindow = SDL_CreateWindow(
			"No window title provided",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			gameWindow->mWidth, gameWindow->mHeight,
			SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE
		);
	}
	
	SDL_assert(
		gameWindow->mWindow &&
		"Unable to create game window. "
		"Continuing will result in a crash."
	);
}

void GameWindow_dtor( GameWindow* gm ){
	SDL_DestroyWindow( gm->mWindow );
}

void GameWindow_handleWindowEvents(
	GameWindow *gameWindow,
	SDL_Event e,
	SDL_Renderer* renderer
){
	if(!gameWindow){ 
		WARNING_MACRO("Warning", "Null argument");
		return;
	}

	if(e.type == SDL_WINDOWEVENT){
		// Depending on the event, the window caption
		// may need to be updated
		bool shouldUpdateCaption = false;

		switch(e.window.event){
			// Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			gameWindow->mWidth = e.window.data1;
			gameWindow->mHeight = e.window.data2;
			break;

			// Repaint after window is not obscured anymore
			case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(renderer);
			break;

			// Window is maximised
			case SDL_WINDOWEVENT_MAXIMIZED:
			gameWindow->mMinimized = false;
			break;
		
			// Window is minimised
			case SDL_WINDOWEVENT_MINIMIZED:
			gameWindow->mMinimized = true;
			break;
		
			// Window is restored
			case SDL_WINDOWEVENT_RESTORED:
			gameWindow->mMinimized = false;
			break;
		}

		// Update window caption with new data
		if(shouldUpdateCaption){
			const char* caption = "new title lol";
			SDL_SetWindowTitle(gameWindow->mWindow, caption);
		}
	}
}

void GameWindow_setFullScreen( GameWindow* gw ){
	//std::cout << "setFullScreen() called\n";
	if( gw->mFullScreen ){
		SDL_SetWindowFullscreen( gw->mWindow, SDL_FALSE );
		gw->mFullScreen = false;
	} else {
		SDL_SetWindowFullscreen( gw->mWindow, SDL_TRUE );
		gw->mFullScreen = true;
		gw->mMinimized = true;
	}
}
