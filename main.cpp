#include <SDL.h>

int main(){
    // SDL setup
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("First Graphics",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          640,
                                          480,
                                          0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);


    //SDL cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}