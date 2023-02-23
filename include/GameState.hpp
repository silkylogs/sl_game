#ifndef GAME_STATE_HEADER_INCLUDED
#define GAME_STATE_HEADER_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "InputHandler.hpp"

// Render the graphics "hello world"
void renderGradient( SDL_Renderer* rend, GameWindow gw, int xOff, int yOff, int zOff ){
	for( int y = 0; y < gw.getHeight(); ++y ){
		for( int x = 0; x < gw.getWidth(); ++x ){
			char r = (float)(x + xOff) / (float)gw.getWidth()  * (float)0xff;
			char g = (float)(y + yOff) / (float)gw.getHeight() * (float)0xff;
			char b = (float)(2 + zOff) / (float)10 * (float)0xff;
			SDL_SetRenderDrawColor( rend, r, g, b, 0xff );
			SDL_RenderDrawPoint( rend, x, y );
	}}

}

class GameState {
	public:
	GameState(){
		mWindowTitle = "Hello world";
		mGameRunning = true;
		
		mGameWindow.init( mWindowTitle, 800, 600 );
		mRenderer = mGameWindow.createRenderer( SDL_RENDERER_SOFTWARE ); 
		
		// Initialize and hook up commands
		mQuitCommand.init( &mGameRunning );
		mInputHandler.assignCommandToButton( SDLK_ESCAPE, &mQuitCommand ); 
		mToggleFullScreenCommand.init( &mGameWindow );
		mInputHandler.assignCommandToButton( SDLK_F12, &mToggleFullScreenCommand );
	
		// test
		mShiftGradientXPlusCmd.init( &xOff );
		mInputHandler.assignCommandToButton( SDLK_d, &mShiftGradientXPlusCmd );
		//
	}

	~GameState(){
		std::cout << "GameState destructor called\n";
		SDL_DestroyRenderer( mRenderer );
		mGameWindow.free();
		SDL_Quit();
	}
	
	bool isGameRunning(){ return mGameRunning; }

	// This is to run every frame
	void update( void ){
		// Handle events on queue
		while( SDL_PollEvent(&mSdlEvent) ){
			// Handling explicit exit request
			if( SDL_QuitRequested() == SDL_TRUE ){
				std::cout << "Explicit quit requested, getting out of main loop...\n";
				mGameRunning = false;
			}
			
			mGameWindow.handeEvent( mSdlEvent, mRenderer );
			Command* inputCmd = mInputHandler.handleInput( mSdlEvent );
			if( inputCmd ) cmd->execute();
		}

		// Draw on screen only when game isnt minimized
		if( !mGameWindow.isMinimized() ) {
			// Clear the screen
			SDL_SetRenderDrawColor( mRenderer, 0xff, 0xff, 0xff, 0xff );
			SDL_RenderClear( mRenderer );

			// Test
			renderGradient( mRenderer, mGameWindow, xOff, 0, 0 );
			
			SDL_RenderPresent( mRenderer );
		}
	}

	private:
	bool mGameRunning;
	GameWindow mGameWindow;
	InputHandler mInputHandler;
		
	std::string mWindowTitle;
	SDL_Renderer* mRenderer;
	SDL_Event mSdlEvent; 

	// Commands
	class QuitCommand: public Command {
		public:
		QuitCommand(){ mExitPtr = nullptr; }

		virtual void execute( void ) {
			std::cout << "Quitting normally...\n";
			if( mExitPtr ) *mExitPtr = false;
			else SDL_assert( 0 &&
				"Warning! QuitCommand points to a null pointer" &&
				"Did you forget to call init() before calling execute()?"
			);
		}

		// Because parameterized constructors dont work in this accursed land
		void init( bool* grb ){
			SDL_assert( grb && "QuitCommand.init() called with null ptr" );
			mExitPtr = grb;
		}

		private:
		bool* mExitPtr;
	} mQuitCommand;

	class ToggleFullScreen: public Command {
		public:
		ToggleFullScreen(){ mGameWindowPtr = nullptr; }

		virtual void execute( void ) {
			std::cout << "Entering fullscreen...\n";
			if( mGameWindowPtr ) mGameWindowPtr->setFullScreen();	
			else SDL_assert( 0 &&
				"Warning! ToggleFullScreen points to a null pointer" &&
				"Did you forget to call init() before calling execute()?"
			);
		}
		
		void init( GameWindow* gwp ){
			SDL_assert( gwp && "ToggleFullScreen.init() called with null ptr" );
			mGameWindowPtr = gwp;
		}

		private:
		GameWindow* mGameWindowPtr;
	} mToggleFullScreenCommand;

	// Temporary test classes used to test input latency, remove asap
	// Things like these should be implemented through GameObjects
	class ShiftGradientXPlusCmd: public Command {
		public:
		ShiftGradientXPlusCmd() { xpOff = nullptr; }

		virtual void execute( void ) {
			std::cout << "Moving right...\n";
			if( xpOff ) *xpOff += 1;
			else SDL_assert( 0 &&
				"Warning! xpOff points to a null pointer" &&
				"Did you forget to call init() before calling execute()?"
			);
		}
		
		void init( int* ip ){
			SDL_assert( ip && "init() called with null ptr" );
			xpOff = ip;
		}

		private:
		int *xpOff;
	} mShiftGradientXPlusCmd;
	int xOff; // more test variables
};

#endif
