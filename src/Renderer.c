#include "Renderer.h"

void Renderer_ctor(
	Renderer* r,
	SDL_Window* w,
	SDL_RendererFlags renderFlags
){
	if( !r ){
		WARNING_MACRO("Warning", "Renderer ptr is null");
		return;
	}
	
	r->mRenderer = SDL_CreateRenderer( w, -1, renderFlags );
	SDL_assert( r->mRenderer && "Unable to create renderer" );
}

void Renderer_dtor( Renderer* r ){
	if( !r ){
		WARNING_MACRO("Warning", "Renderer ptr is null");
		return;
	}

	SDL_DestroyRenderer( r->mRenderer );
	r->mRenderer = NULL;
}

void Renderer_clearScreen( Renderer* r ) {
	if( !r ){
		WARNING_MACRO("Warning", "Renderer ptr is null");
		return;
	}
	SDL_SetRenderDrawColor( r->mRenderer, 0xff, 0xff, 0xff, 0xff );
	SDL_RenderClear( r->mRenderer );
}

void Renderer_renderPresent( Renderer* r ){
	if( !r ){
		WARNING_MACRO("Warning", "Renderer ptr is null");
		return;
	}
	SDL_RenderPresent( r->mRenderer );
}

void Renderer_setRendererColor( unsigned int hex ) {
	/*char r = (unsigned int)hex << 24;
	char g = (unsigned int)hex << 16;
	char b = (unsigned int)hex << 08;
	char a = (unsigned int)hex << 00;
	SDL_SetRenderDrawColor( mRenderer, r, g, b, a );
	*/
}

SDL_Renderer* Renderer_getRenderer( Renderer* r ) {
	if( !r ){
		WARNING_MACRO("Warning", "Renderer ptr is null");
		return NULL;
	}
	return r->mRenderer;
}
