/* main.c */

#include "SDL.h"

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    
    SDL_SetVideoMode(640, 480, 8, SDL_SWSURFACE);
    SDL_Delay(3000);
    
    return 0;
}