#ifndef GAME_MAIN_HEADER_INCLUDED
#define GAME_MAIN_HEADER_INCLUDED

// Todo: make input async via multithreading

#include <SDL2/SDL.h>

#include "GameWindow.h"
#include "InputHandler2.h"
#include "Renderer.h"

typedef struct GameMain {
	const char*     mWindowTitle;
	SDL_Event       mSdlEvent; 
	
	bool            mGameRunning;
	GameWindow      mGameWindow;
	Renderer        mGameRenderer;
	InputHandler2   mInputHandler2;
} GameMain;

const char* gWindowTitle = "Hello world";

// Render the graphics "hello world"
void renderGradient(
	SDL_Renderer* rend,
	GameWindow gw,
	int xOff, int yOff, int zOff
){
	int x=0;
	int y=0;
	for(y=0; y < GameWindow_getHeight(&gw); ++y){
		for(x=0; x < GameWindow_getWidth(&gw); ++x){
			char r =
			(float)(x-xOff) / 
			(float)GameWindow_getWidth(&gw) * 
			(float)0xff;
			
			char g = (float)(y-yOff) /
			(float)GameWindow_getHeight(&gw) * 
			(float)0xff;
			
			char b = (float)(2-zOff)/(float)10*(float)0xff;

			SDL_SetRenderDrawColor( rend, r, g, b, 0xff );
			SDL_RenderDrawPoint( rend, x, y );
}}}

void quitCallback(void* gameMainPtr){
	GameMain* gmPtr = (GameMain*)gameMainPtr;
	if(gmPtr){
		gmPtr->mGameRunning = false;
	}
}

void GameMain_ctor(GameMain* gameMain){
	gameMain->mGameRunning = true;
	gameMain->mWindowTitle = gWindowTitle;
	
	GameWindow_ctor(
		&gameMain->mGameWindow,
		gameMain->mWindowTitle,
		800, 600
	);

	Renderer_ctor(
		&gameMain->mGameRenderer,
		GameWindow_getWindow( &gameMain->mGameWindow ),
		SDL_RENDERER_SOFTWARE
	);
	
	// The input handler
	InputHandler2_ctor( &gameMain->mInputHandler2 );

	// Hook up commands to the input handler
	InputHandler2_assignCallbackToButton(
		&gameMain->mInputHandler2,
		SDLK_ESCAPE,
		&quitCallback
	);
}

void GameMain_dtor(GameMain* gameMain){
	printf("GameMain destructor called\n");
	GameWindow_dtor(&gameMain->mGameWindow);
	SDL_Quit();
}

// This is to run every frame
void GameMain_update(GameMain* gm){
	
	// Handle events on queue
	while( SDL_PollEvent(&gm->mSdlEvent) ){
	
		// Handling explicit exit request
		if( SDL_QuitRequested() == SDL_TRUE ){
			printf(	"Explicit quit requested, "
				"getting out of main loop...\n");
			gm->mGameRunning=false;
		}
		
		GameWindow_handleWindowEvents(
			&gm->mGameWindow,
			gm->mSdlEvent,
			Renderer_getRenderer( &gm->mGameRenderer )
		);
		
		Command2* c2 = InputHandler2_handleInput(
			&gm->mInputHandler2, gm->mSdlEvent
		);
	
		if(c2) c2(gm);
	}

	// Draw on screen only when game isnt minimized
	if( !GameWindow_isMinimized(&gm->mGameWindow) ) {
		Renderer_clearScreen( &gm->mGameRenderer );
		renderGradient(
			Renderer_getRenderer( &gm->mGameRenderer ),
			gm->mGameWindow,
			0, 0, 0
		);
		Renderer_renderPresent( &gm->mGameRenderer );
	}
}

bool GameMain_isGameRunning(GameMain* gm){
	return gm->mGameRunning;
}

#undef WARNING_MACRO
#endif
