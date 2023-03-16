#include <SDL.h>
#include <vector>
#include <iostream>

struct Colour{
    int rval,gval,bval;

    Colour(int r, int g, int b){
      rval = r;
      gval = g;
      bval = b;
    }
};

std::ostream& operator<<(std::ostream& os, Colour c){
  return os << c.rval << ", " << c.gval << ", " << c.bval << "\n";
}

class Canvas{
private:
    SDL_Renderer *sdlRenderer;

public:
    Canvas(SDL_Renderer *aSdlRenderer) {
        this->sdlRenderer = aSdlRenderer;
    }

    void setBgColor(int r, int g, int b){
        SDL_SetRenderDrawColor(sdlRenderer, r, g, b, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderPresent(sdlRenderer);
    }
};

int main(int argv, char** args){
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

    Canvas canvas(renderer);

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
        //SDL_RenderClear(renderer);
        canvas.setBgColor(255,255,0);
        //SDL_RenderPresent(renderer);
    }
    //SDL cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;

}