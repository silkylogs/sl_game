#ifndef GAME_MAIN_HEADER_INCLUDED
#define GAME_MAIN_HEADER_INCLUDED

// todo: and also implement the renderer class

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "InputHandler.hpp"
#include "Renderer.hpp"

// Render the graphics "hello world"
void renderGradient( SDL_Renderer* rend, GameWindow gw, int xOff, int yOff, int zOff ){
	for( int y = 0; y < gw.getHeight(); ++y ){
		for( int x = 0; x < gw.getWidth(); ++x ){
			char r = (float)(x - xOff) / (float)gw.getWidth()  * (float)0xff;
			char g = (float)(y - yOff) / (float)gw.getHeight() * (float)0xff;
			char b = (float)(2 - zOff) / (float)10 * (float)0xff;
			SDL_SetRenderDrawColor( rend, r, g, b, 0xff );
			SDL_RenderDrawPoint( rend, x, y );
	}}

}

class GameMain {
	public:
	GameMain():
		// Game systems
		mWindowTitle{"Hello world"},
		mSdlEvent{},
		
		mGameRunning{ true },
		mGameWindow{ mWindowTitle, 800, 600 },
		mGameRenderer{ mGameWindow.getWindow(), SDL_RENDERER_SOFTWARE },
		
		// Game commands
		mQuitCommand             { mGameRunning },
		mToggleFullScreenCommand { mGameWindow },

		// The input handler
		mInputHandler{}

	{
		mWindowTitle = "Hello world";
		mGameRunning = true;
		
		// Hook up commands to the input handler
		mInputHandler.assignCommandToButton( SDLK_ESCAPE, &mQuitCommand ); 
		mInputHandler.assignCommandToButton( SDLK_F12, &mToggleFullScreenCommand );
	
		// test
			mShiftGradientXPlusCmd.init( &xOff );
			mInputHandler.assignCommandToButton( SDLK_d, &mShiftGradientXPlusCmd );
		//
	}

	~GameMain(){
		std::cout << "GameMain destructor called\n";
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
			
			mGameWindow.handleEvent( mSdlEvent, mGameRenderer.getRenderer() );
			Command* inputCmd = mInputHandler.handleInput( mSdlEvent );
			if( inputCmd ) inputCmd->execute();
		}

		// Draw on screen only when game isnt minimized
		if( !mGameWindow.isMinimized() ) {
			mGameRenderer.clearScreen();
			renderGradient( mGameRenderer.getRenderer(), mGameWindow, xOff, 0, 0 );
			mGameRenderer.renderPresent();
		}
	}

	private:
	std::string     mWindowTitle;
	SDL_Event       mSdlEvent; 
	
	bool            mGameRunning;
	GameWindow      mGameWindow;
	Renderer        mGameRenderer;
		

	// Commands
	class QuitCommand: public Command {
		public:
		QuitCommand( bool& exitRef ): mExitRef{ exitRef } {}

		virtual void execute( void ) {
			mExitRef = false;
		}

		private:
		bool& mExitRef;
	} mQuitCommand;

	class ToggleFullScreenCommand: public Command {
		public:
		ToggleFullScreenCommand( GameWindow& gameWindowRef ): mGameWindowRef{ gameWindowRef } {}

		virtual void execute( void ){
			std::cout << "Entering fullscreen...\n";
			mGameWindowRef.setFullScreen();
		}

		private:
		GameWindow& mGameWindowRef;
	} mToggleFullScreenCommand;
	
	InputHandler    mInputHandler;


	
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
