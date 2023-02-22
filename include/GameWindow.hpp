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
	GameWindow(){
		mWindow = NULL;
		mWidth = 0;
		mHeight = 0;
		mMouseFocus = false;
		mKeyboardFocus = false;
		mFullScreen = false;
		mMinimized = false;
	}

	// Initialize window with settings
	void init( std::string& windowTitle, int windowWidth, int windowHeight ){
		SDL_assert( windowWidth > 0 && "Argument has invalid window width" );
		SDL_assert( windowHeight > 0 && "Argument has invalid window height" );
		
		mWidth = windowWidth;
		mHeight = windowHeight;
		
		// Create the window
		mWindow = SDL_CreateWindow(
			windowTitle.c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			mWidth, mHeight,
			SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE
		);

		SDL_assert( mWindow && "Unable to create window" );
	}

	// Create a renderer using the sdl window context
	SDL_Renderer* createRenderer( SDL_RendererFlags renderFlags ){
		SDL_assert( mWindow && "Warning: member SDL_Window pointer is null" );
		
		SDL_Renderer* r = SDL_CreateRenderer( mWindow, -1, renderFlags );
		SDL_assert( r && "Unable to create renderer" );
		
		return r;
	}

	// Handles keyboard and window events,
	// even though this module should only handle window events
	void handeEvent( SDL_Event& e, SDL_Renderer* renderer ){
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

	void setFullScreen(){
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

	void free(){ SDL_DestroyWindow( mWindow ); }
	int getWidth(){ return mWidth; }
	int  getHeight(){ return mHeight; }
	bool hasMouseFocus(){ return mMouseFocus; }
	bool hasKeyboardFocus(){ return mKeyboardFocus; }
	bool isMinimized(){ return  mMinimized; }
};

#endif
