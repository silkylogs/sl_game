#ifndef GAME_STATE_HEADER_INCLUDED
#define GAME_STATE_HEADER_INCLUDED

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "InputHandler.hpp"

class GameState {
	public:
	GameState(){
		mHeight = 600;
		mWidth = 800;
		mWindowTitle = "Hello game";
		mGameRunning = true;
		
		
		mGameWindow.init( mWindowTitle, mWidth, mHeight );
		mRenderer = mGameWindow.createRenderer( SDL_RENDERER_SOFTWARE ); 
		
		// Initialize and hook up commands
		mQuitCommand.init( &mGameRunning );
		mInputHandler.assignCommandToButton( SDLK_ESCAPE, &mQuitCommand ); 
		
		mToggleFullScreenCommand.init( &mGameWindow );
		mInputHandler.assignCommandToButton( SDLK_F12, &mToggleFullScreenCommand );
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
			Command* cmd = mInputHandler.handleInput( mSdlEvent.key.keysym.sym );
			if( cmd ) cmd->execute();
		}

		// Draw on screen only when game isnt minimized
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

	// Todo: make this not continously toggle on and off when button is held down
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
};

#endif
