#ifndef GAME_RENDERER_HEADER_INCLUDED
#define GAME_RENDERER_HEADER_INCLUDED

#include <SDL2/SDL.h>

class Renderer {
	public:
	// Initializes internal renderer with the valid SDL_Window pointer 
	void init( SDL_Window*, SDL_RendererFlags );
	void dtor();
	
	void clearScreen();
	void renderPresent();
	void drawPixel( int x, int y );
	void setRendererColor( unsigned int hex ); // warning: unimplemented
	SDL_Renderer* getRenderer();

	private:
	SDL_Renderer* mRenderer;
};

void Renderer::init( SDL_Window* w, SDL_RendererFlags renderFlags ) {
	SDL_assert( w && "Warning: SDL_Window pointer is null" );
	
	mRenderer = SDL_CreateRenderer( w, -1, renderFlags );
	SDL_assert( mRenderer && "Unable to create renderer" );
}

void Renderer::dtor(){
	SDL_DestroyRenderer( mRenderer );
	mRenderer = nullptr;
}

void Renderer::clearScreen() {
	SDL_SetRenderDrawColor( mRenderer, 0xff, 0xff, 0xff, 0xff );
	SDL_RenderClear( mRenderer );
}

void Renderer::renderPresent(){
	SDL_RenderPresent( mRenderer );
}

void Renderer::setRendererColor( unsigned int hex ) {
	/*char r = (unsigned int)hex << 24;
	char g = (unsigned int)hex << 16;
	char b = (unsigned int)hex << 08;
	char a = (unsigned int)hex << 00;
	SDL_SetRenderDrawColor( mRenderer, r, g, b, a );
	*/
}


SDL_Renderer* Renderer::getRenderer() { return mRenderer; }

#endif
