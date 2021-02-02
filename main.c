/* main.c */

#include "SDL.h"

#define MAX_FPS 60
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct polygo {
    float x[3];
    float y[3];
    Uint8 color;
} polygon;


/* Put pixel at x,y with 8-bit color-depth. */
void putpx(SDL_Surface *surf, int x, int y, Uint8 color) {
    ( (Uint8*)surf->pixels+y*WINDOW_HEIGHT)[x] = color;
}

void draw_polygons(SDL_Surface *surf, polygon *polys);

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    
    /* 8-bit true color: rrrgggbb. */
    SDL_Surface *screen;
    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 8, SDL_SWSURFACE); /* Screen with 8-bit color depth. */
    
    int quit = 0;
    SDL_Event event;
    while(!quit) {
        
        /* process events */
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    if(event.key.keysym.sym == SDLK_ESCAPE) {
                        quit = 1;
                    }
                    break;
                default:
                    break;
            }
        }
        
        
        SDL_FillRect(screen, NULL, 033); /* Fill whole screen with light blue. */
        
        int i;
        for(i=0; i<100; i++)
        putpx(screen, i, 100, (Uint8)0);

        SDL_UpdateRect(screen, 0, 0, 0, 0); /* Update whole screen. */
        SDL_Delay(1000/MAX_FPS); /* Limit FPS. */
    }
    
    return 0;
}