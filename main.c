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
void put_pixel(SDL_Surface *surf, int x, int y, Uint8 color) {
    ( (Uint8*)surf->pixels+y*surf->w)[x] = color;
}

void draw_line(SDL_Surface *surf, float x1, float x2, float y1, float y2, Uint8 color) {
    /*
    Rasterizing line by casting coordinates to int. Using linear equation to calculate
    points. Consider y-Axis pointing downwards. */
    float m = (y2 - y1) / (x1 - x2); /* slope */
    float b = m*x2 + y2; /* y-intersect */
    
    float x, y;
    for(x=x1; x<x2; x+=1) {
        y = -m*x + b; /* linear equation */
        put_pixel(surf, (int)x, (int)y, color);
    }
    
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
    float x1=0, y1=0;
    while(!quit) {
        
        /* process events */
        while(SDL_PollEvent(&event)) {
            switch(event.type) {
                case SDL_QUIT:
                    quit = 1;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            quit = 1;
                            break;
                        case SDLK_w:
                            y1 = y1 - 5.5;
                            break;
                        case SDLK_a:
                            x1 = x1 - 5.5;
                            break;
                        case SDLK_s:
                            y1 = y1 + 5.5;
                            break;
                        case SDLK_d:
                            x1 = x1 + 5.5;
                            break;  
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        
        
        SDL_FillRect(screen, NULL, 033); /* Fill whole screen with light blue. */
        draw_line(screen, x1, 300, y1, 100, (Uint8)0); /* Black line. */

        SDL_UpdateRect(screen, 0, 0, 0, 0); /* Update whole screen. */
        SDL_Delay(1000/MAX_FPS); /* Limit FPS. */
        fflush(stdout);
    }
    
    return 0;
}