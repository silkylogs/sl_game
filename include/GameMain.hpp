#ifndef GAME_MAIN_HEADER_INCLUDED
#define GAME_MAIN_HEADER_INCLUDED

// Todo: convert project to C (ANSI if possible)
// Todo: make input async via multithreading

#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>

#include "GameWindow.hpp"
#include "InputHandler.hpp" // deprecated
#include "InputHandler2.h"
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
		
	QuitCommand     mQuitCommand; // Part of deprecated command, modify
	Command2*       mQuitCommand2;
	
	InputHandler    mInputHandler;// part of cmd
	InputHandler2   mInputHandler2;
};

void GameMain_ctor(GameMain* gameMain){
	InputHandler2_ctor(&gameMain->mInputHandler2);

	// Game systems
	gameMain->mGameRunning = true;
	gameMain->mGameWindow.init(gameMain->mWindowTitle, 800, 600);
	gameMain->mGameRenderer
		.init(gameMain->mGameWindow.getWindow(), SDL_RENDERER_SOFTWARE);
	
	// Game commands
	gameMain->mQuitCommand.ctor(&gameMain->mGameRunning);//part of cmd

	// The input handler
	InputHandler_ctor(&gameMain->mInputHandler);//part of cmd

	gameMain->mWindowTitle="Hello world";
	gameMain->mGameRunning=true;
		
	// Hook up commands to the input handler
	InputHandler_assignCommandToButton( // part of cmd
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
		Command* inputCmd=InputHandler_handleInput// part of cmd
			(&gm->mInputHandler,gm->mSdlEvent);
		if(inputCmd)inputCmd->execute();// part of cmd
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
