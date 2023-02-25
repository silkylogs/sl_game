#ifndef GAMEWINDOW_HEADER_INCLUDED
#define GAMEWINDOW_HEADER_INCLUDED

#include <SDL2/SDL.h>

// A more robust wrapper for the game window
class GameWindow {
	private:
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

	public:
	GameWindow( std::string& windowTitle, int wWidth, int wHeight );

	// Handles window events
	void handleEvent( SDL_Event& e, SDL_Renderer* renderer );

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

GameWindow::GameWindow( std::string& windowTitle, int wWidth, int wHeight ):
	mWindow        { nullptr },
	mWidth         { wWidth },
	mHeight        { wHeight },
	mMouseFocus    { false },
	mKeyboardFocus { false },
	mFullScreen    { false },
	mMinimized     { false }
{
	if( mWidth <= 0 ) {
		std::cerr
			<< "Argument has an invalid window width. (x == "
			<< mWidth
			<< ") Continuting with a safer width...\n";
		mWidth = 300;
	}
	
	if( mHeight < 0 ) {
		std::cerr
			<< "Argument has an invalid window height. (y == "
			<< mHeight
			<< ") Continuting with a safer height...\n";
		mHeight = 200;
	}
	
	mWindow = SDL_CreateWindow(
		windowTitle.c_str(),
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		mWidth, mHeight,
		SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE
	);
	
	SDL_assert( mWindow && "Unable to create game window. Continuing will result in a crash." );
}

void GameWindow::handleEvent( SDL_Event& e, SDL_Renderer* renderer ){
	if( e.type == SDL_WINDOWEVENT ){
		// Depending on the event, the window caption may need to be updated
		bool shouldUpdateCaption = false;

		switch( e.window.event ){
			// Get new dimensions and repaint on window size change
			case SDL_WINDOWEVENT_SIZE_CHANGED:
			mWidth = e.window.data1;
			mHeight = e.window.data2;
			break;

			// Repaint after window is not obscured anymore
			case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent( renderer );
			break;

			// Window is maximised
			case SDL_WINDOWEVENT_MAXIMIZED:
			mMinimized = true;
			break;
		
			// Window is minimised
			case SDL_WINDOWEVENT_MINIMIZED:
			mMinimized = true;
			break;
		
			// Window is restored
			case SDL_WINDOWEVENT_RESTORED:
			mMinimized = false;
			break;
		
		}

		// Update window caption with new data
		if( shouldUpdateCaption ){
			std::stringstream caption;
			caption << "new title lol";
			SDL_SetWindowTitle( mWindow, caption.str().c_str() );
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
