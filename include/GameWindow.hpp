#ifndef GAMEWINDOW_HEADER_INCLUDED
#define GAMEWINDOW_HEADER_INCLUDED

#include <SDL2/SDL.h>
// Prints a warning to stderr in the form
// <filename>:<linenumber>:<functionName>(): <warningLevel>: <moreDetails>
#define WARNING_MACRO(WLEVEL,WSTRING)\
	fprintf(stderr,\
		"%s:%d:%s(): %s: %s\n",\
		__FILE__, __LINE__, __func__,\
		WLEVEL, WSTRING);

// A more robust wrapper for the game window
struct GameWindow {
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

	// Handles window events
	//void handleEvent( SDL_Event& e, SDL_Renderer* renderer );

	// Toggles full screen
	void setFullScreen();

	// Manual destructor
	void free(){
		SDL_DestroyWindow( mWindow );
	}
	
	// Getters
	int  getWidth()         { return mWidth; }
	int  getHeight()        { return mHeight; }
	bool hasMouseFocus()    { return mMouseFocus; }
	bool hasKeyboardFocus() { return mKeyboardFocus; }
	bool isMinimized()      { return mMinimized; }
	SDL_Window* getWindow() { return mWindow; }
};

void GameWindow_ctor( 
	GameWindow* gameWindow,
	std::string& windowTitle,
	int wWidth, int wHeight
){
	if(!gameWindow){ 
		WARNING_MACRO("Warning", "Null argument");
		return;
	}

	gameWindow->mHeight        = wHeight;
	gameWindow->mWidth         = wWidth;
	gameWindow->mMouseFocus    = false ;
	gameWindow->mKeyboardFocus = false ;
	gameWindow->mFullScreen    = false ;
	gameWindow->mMinimized     = false ;
	gameWindow->mWindow        = NULL  ;

	if( gameWindow->mWidth <= 0 ) {
		fprintf(stderr,
			"%s:%d:%s():"
			"Argument has an invalid window width. (x == %d)"
			"Continuting with a safer width...\n",
			__FILE__, __LINE__, __func__, gameWindow->mWidth
		);
		gameWindow->mWidth = 300;
	}
	
	if( gameWindow->mHeight <= 0 ) {
		fprintf(stderr,
			"%s:%d:%s():"
			"Argument has an invalid window height. (x == %d)"
			"Continuting with a safer height...\n",
			__FILE__, __LINE__, __func__, gameWindow->mHeight
		);
		gameWindow->mHeight = 200;
	}
	
	gameWindow->mWindow = SDL_CreateWindow(
		windowTitle.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		gameWindow->mWidth, gameWindow->mHeight,
		SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE
	);
	
	SDL_assert(
		gameWindow->mWindow &&
		"Unable to create game window. "
		"Continuing will result in a crash."
	);
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

void GameWindow::setFullScreen(){
	std::cout << "setFullScreen() called\n";
	if( mFullScreen ){
		SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
		mFullScreen = false;
	} else {
		SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
		mFullScreen = true;
		mMinimized = true;
	}
}

#endif
