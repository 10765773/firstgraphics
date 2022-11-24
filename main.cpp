#include <SDL.h>

int main(){
    bool quit;
    SDL_Event event;
    // SDL setup
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("First Graphics",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          1080,
                                          720,
                                          0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    //Main loop
    while(!quit){
        SDL_Delay(10);
        //Event handling
        SDL_PollEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                quit = true;
                break;
        }
        SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
    }
    //SDL cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}