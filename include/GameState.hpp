#ifndef GAME_STATE_HEADER_INCLUDED
#define GAME_STATE_HEADER_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "InputHandler.hpp"

// Note to OOPhiles: there is no need to derive this class
class GameState {
	public:
	GameState(){
		mHeight = 600;
		mWidth = 800;
		mWindowTitle = "Hello game";
		mGameRunning = true;

		mGameWindow.init( mWindowTitle, mWidth, mHeight );
		mRenderer = mGameWindow.createRenderer( SDL_RENDERER_SOFTWARE ); 
	}

	~GameState(){
		std::cout << "GameState destructor called\n";
		SDL_DestroyRenderer( mRenderer );
		mGameWindow.free();
		SDL_Quit();
	}
	
	bool isGameRunning(){ return mGameRunning; }

	// Run this every frame
	void update( void ){
		// Handle events on queue
		while( SDL_PollEvent(&mSdlEvent) ){
			// Handling explicit exit request
			if( SDL_QuitRequested() == SDL_TRUE ){
				std::cout << "Explicit quit requested, getting out of main loop...\n";
				mGameRunning = false;
			}
			
			mGameWindow.handeEvent( mSdlEvent, mRenderer );
			Command* cmd = mInputHandler.handleInput( mSdlEvent );
			//std::cout << "Addr of cmd: " << cmd << "\n";
			GameObject tempGo;
			cmd->execute( tempGo );
		}

		if( !mGameWindow.isMinimized() ) {
			// Clear the screen
			SDL_SetRenderDrawColor( mRenderer, 0xff, 0xff, 0xff, 0xff );
			SDL_RenderClear( mRenderer );

			// Render the graphics "hello world"
			for( int y = 0; y < mGameWindow.getHeight(); ++y ){
				for( int x = 0; x < mGameWindow.getWidth(); ++x ){
					char r = (float)x / (float)mGameWindow.getWidth()  * (float)0xff;
					char g = (float)y / (float)mGameWindow.getHeight() * (float)0xff;
					char b = (float)2 / (float)10 * (float)0xff;
					SDL_SetRenderDrawColor( mRenderer, r, g, b, 0xff );
					SDL_RenderDrawPoint( mRenderer, x, y );
			}}
			
			SDL_RenderPresent( mRenderer );
		}
	}

	private:
	bool mGameRunning;
	GameWindow mGameWindow;
	InputHandler mInputHandler;
		
	std::string mWindowTitle;
	int mWidth;
	int mHeight;
	SDL_Renderer* mRenderer;
	SDL_Event mSdlEvent; 
};

#endif
