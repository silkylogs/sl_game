#ifndef GAME_MAIN_HEADER_INCLUDED
#define GAME_MAIN_HEADER_INCLUDED

// Todo: convert project to C (ANSI if possible)
// Todo: make input async via multithreading

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "InputHandler.hpp"
#include "Renderer.hpp"

// Render the graphics "hello world"
void renderGradient(
	SDL_Renderer* rend,
	GameWindow gw,
	int xOff, int yOff, int zOff
){
	int x=0;
	int y=0;
	for(y=0;y<gw.getHeight();++y){
		for(x=0;x<gw.getWidth();++x){
			char r =
			(float)(x-xOff)/(float)gw.getWidth()*(float)0xff;
			char g =
			(float)(y-yOff)/(float)gw.getHeight()*(float)0xff;
			char b =
			(float)(2-zOff)/(float)10*(float)0xff;

			SDL_SetRenderDrawColor( rend, r, g, b, 0xff );
			SDL_RenderDrawPoint( rend, x, y );
}}}

// Commands
class QuitCommand: public Command {
	public:
	void ctor( bool* exitRef ){ mExitRef = exitRef; };

	virtual void execute( void ) {
		*mExitRef = false;
	}

	bool* mExitRef;
};

struct GameMain {
	std::string     mWindowTitle;
	SDL_Event       mSdlEvent; 
	
	bool            mGameRunning;
	GameWindow      mGameWindow;
	Renderer        mGameRenderer;
		
	QuitCommand     mQuitCommand;
	InputHandler    mInputHandler;
};

void GameMain_ctor(GameMain* gameMain){
	// Game systems
	gameMain->mGameRunning = true;
	gameMain->mGameWindow.init(gameMain->mWindowTitle, 800, 600);
	gameMain->mGameRenderer
		.init(gameMain->mGameWindow.getWindow(), SDL_RENDERER_SOFTWARE);
	
	// Game commands
	gameMain->mQuitCommand.ctor(&gameMain->mGameRunning);

	// The input handler
	InputHandler_ctor(&gameMain->mInputHandler);

	gameMain->mWindowTitle="Hello world";
	gameMain->mGameRunning=true;
		
	// Hook up commands to the input handler
	InputHandler_assignCommandToButton(
		&gameMain->mInputHandler,
		SDLK_ESCAPE,&gameMain->mQuitCommand); 
}

void GameMain_dtor(GameMain* gameMain){
	printf("GameMain destructor called\n");
	gameMain->mGameWindow.free();
	SDL_Quit();
}

// This is to run every frame
void GameMain_update(GameMain* gm){
	// Handle events on queue
	while(SDL_PollEvent(&gm->mSdlEvent)){
		// Handling explicit exit request
		if(SDL_QuitRequested()==SDL_TRUE){
			printf(
			"Explicit quit requested, "
			"getting out of main loop...\n");
			gm->mGameRunning=false;
		}
		
		gm->mGameWindow.handleEvent
			(gm->mSdlEvent,gm->mGameRenderer.getRenderer());
		Command* inputCmd=InputHandler_handleInput
			(&gm->mInputHandler,gm->mSdlEvent);
		if(inputCmd)inputCmd->execute();
	}

	// Draw on screen only when game isnt minimized
	if( !gm->mGameWindow.isMinimized() ) {
		gm->mGameRenderer.clearScreen();
		renderGradient(
			gm->mGameRenderer.getRenderer(),
			gm->mGameWindow,
			0, 0, 0 );
		gm->mGameRenderer.renderPresent();
	}
}

bool GameMain_isGameRunning(GameMain* gm){return gm->mGameRunning;}
#endif
