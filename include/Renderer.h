#ifndef GAME_RENDERER_HEADER_INCLUDED
#define GAME_RENDERER_HEADER_INCLUDED

#include <SDL2/SDL.h>

#define WARNING_MACRO(WLEVEL,WSTRING)\
	fprintf(stderr,\
		"%s:%d:%s(): %s: %s\n",\
		__FILE__, __LINE__, __func__,\
		WLEVEL, WSTRING);

typedef struct Renderer {
	SDL_Renderer* mRenderer;
} Renderer;

// Initializes internal renderer with a valid SDL_Window pointer 
void Renderer_ctor( Renderer* r, SDL_Window* w, SDL_RendererFlags renderFlags );
void Renderer_dtor( Renderer* r );

void Renderer_clearScreen( Renderer* r );
void Renderer_renderPresent( Renderer* r );
void Renderer_setRendererColor( unsigned int hex );
void Renderer_setPixel( Renderer* r, int x, int y );
SDL_Renderer* Renderer_getRenderer( Renderer* r );

#endif
