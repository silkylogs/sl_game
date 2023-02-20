#include <iostream>
#include <SDL2/SDL.h>

struct Window {
	int screenWidth ;
	int screenHeight;
	SDL_Window* sdlWindow;
	SDL_Renderer* sdlRenderer;
};

void initSDLComponents( struct Window* gameWindow ){
	// Create window
	gameWindow->sdlWindow = SDL_CreateWindow(
		"game",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		gameWindow->screenWidth, gameWindow->screenHeight,
		SDL_WINDOW_SHOWN );
	SDL_assert( gameWindow->sdlWindow && "Unable to create window" );

	// Create renderer for window
	gameWindow->sdlRenderer = SDL_CreateRenderer( gameWindow->sdlWindow, -1, SDL_RENDERER_SOFTWARE );
	SDL_assert( gameWindow->sdlRenderer && "Unable to create renderer" );

	// Initialize render color and mode
	SDL_SetRenderDrawBlendMode( gameWindow->sdlRenderer, SDL_BLENDMODE_BLEND );
	SDL_SetRenderDrawColor( gameWindow->sdlRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE );
	
	// Initialize text rendering
	//TTF_Init();
}

void shutdownSDLComponents( struct Window* gameWindow ){
	//TTF_Quit();

	SDL_DestroyRenderer( gameWindow->sdlRenderer );
	SDL_DestroyWindow( gameWindow->sdlWindow );
	gameWindow->sdlWindow   = NULL;
	gameWindow->sdlRenderer = NULL;
	SDL_Quit();
}

int main(void){
	Window w = {0};
	w.screenWidth = 800;
	w.screenHeight = 600;

	initSDLComponents( &w );

	SDL_Event e;
	bool gameRunning = true;
	while( gameRunning ) {
		while( SDL_PollEvent(&e) != 0 ){
			if( e.type == SDL_QUIT ) gameRunning = false;
			else if( e.type == SDL_KEYDOWN ){
				switch( e.key.keysym.sym ){
				case SDLK_ESCAPE:
					gameRunning = false;
					break;
				}
			}
		}
	
		for( int y = 0; y < 600; ++y ){
			for( int x = 0; x < 800; ++x ){
				char r = (float)x / (float)800 * (float)0xff;
				char g = (float)y / (float)800 * (float)0xff;
				char b = (float)400 / (float)800 * (float)0xff;
				SDL_SetRenderDrawColor( w.sdlRenderer, r, g, b, 0xff );
				SDL_RenderDrawPoint( w.sdlRenderer, x, y );
			}
		}
			
		SDL_RenderPresent( w.sdlRenderer );
	}
	
	

	shutdownSDLComponents( &w );
	return 0;
}

