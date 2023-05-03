#include "glad.h"
#include <SDL.h>
#include <iostream>

SDL_Window *window;
SDL_GLContext glContext;
SDL_Event event;
bool sdlQuit;

void eventHandle(){
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            sdlQuit = true;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    sdlQuit = true;
            }
    }
}




int main(int argv, char** args){
    sdlQuit = false;

    // SDL setup
    //Use OpenGL 3.3 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Initialise video subsystem
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    //Create SDL window
    window = SDL_CreateWindow( "First Graphics",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               1080,
                               720,
                               SDL_WINDOW_OPENGL);
    if(window == NULL){
        std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    //Create OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if(glContext == NULL){
        std::cout << "OpenGL context could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    //Initialize glad
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //Set OpenGL viewport size
    glViewport(0, 0, 1080, 720);

    //Main loop
    while(!sdlQuit){
        SDL_Delay(10);
        //Event handling
        eventHandle();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(window);
    }

    //SDL cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}