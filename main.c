/* main.c */

#include <time.h>
#include "SDL.h"

#define MAX_FPS 60
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

typedef struct polygo {
    float x[3];
    float y[3];
    Uint8 color;
} polygon;

/* Simple swap-function. */
void swap_float(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

float abs_float(float a) {
    return (a >= 0) ? a : -a;
}

float min_float(float a, float b) {
    return (a <= b) ? a : b;
}

float max_float(float a, float b) {
    return (a >= b) ? a : b;
}

/* Put pixel at x,y with 8-bit color-depth. Negtive coordinates aren't drawn. */
void put_pixel(SDL_Surface *surf, int x, int y, Uint8 color) {
    if(x < 0 || y < 0 || y >= surf->h || x >= surf->w) return;
    ( (Uint8*)surf->pixels+y*surf->w)[x] = color;
}

void draw_line(SDL_Surface *surf, float x1, float x2, float y1, float y2, Uint8 color) {
    
    /* Draw point. */
    if(x1 == x2 && y1 == y2) {
        put_pixel(surf, (int)x1, (int)y1, color);
        return;
    }
    /* Draw vertical line. */
    if(x2 == x1) {
        float ymin, ymax;
        ymin = min_float(y1, y2);
        ymax = max_float(y1, y2);
        
        float y;
        for(y=ymin; y<ymax; y+=1) {
            put_pixel(surf, (int)x1, (int)y, color);
        }
        
        return;   
    }
    
    /*Rasterizing line by casting coordinates to int. Using linear equation to calculate
    points. Keep in mind that y-axis is pointing downwards. */
    float m = (y2 - y1) / (x2 - x1); /* slope */
    float b = y2 - m*x2; /* y-intersect */
    
    float x, y;
    /* If m < 1 then we iterate over x. */
    if(abs_float(m) <= 1) {
        
        /* This ensures that x1 is always less then x2. */
        if(x1 > x2) {
            swap_float(&x1, &x2);
            swap_float(&y1, &y2); /* If x is swapped, y needs to be swapped to. */
        }
        
        for(x=x1; x<x2; x+=1) {
            y = m*x + b; /* linear equation */
            put_pixel(surf, (int)x, (int)y, color);

        }
    } else {
        if(y1 > y2) {
            swap_float(&x1, &x2);
            swap_float(&y1, &y2);
        }
        
        for(y=y1; y<y2; y+=1) {
            x = (y-b) / m; /* inverse function */
            put_pixel(surf, (int)x, (int)y, color);

        }
    } 
    
}

void random_lines(SDL_Surface *surf, int iter) {
    srand(time(NULL));
    int color;
    float x1, x2, y1, y2;
    for(;iter>0; iter--) {
        x1 = (float)rand() / RAND_MAX * surf->w;
        x2 = (float)rand() / RAND_MAX * surf->w;
        y1 = (float)rand() / RAND_MAX * surf->h;
        y2 = (float)rand() / RAND_MAX * surf->h;
        color = rand() % 256;
        draw_line(surf, x1, x2, y1, y2, color);
        
        
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
        
        
        SDL_UpdateRect(screen, 0, 0, 0, 0); /* Update whole screen. */
        SDL_Delay(1000/MAX_FPS); /* Limit FPS. */
        fflush(stdout);
    }
    
    return 0;
}