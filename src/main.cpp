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

const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                   "}\n\0";

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
    if(window == nullptr){
        std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    //Create OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if(glContext == nullptr){
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

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);


    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);


    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // TR
            0.5f, -0.5f, 0.0f,  // BR
            -0.5f, -0.5f, 0.0f,  // BL
            -0.5f,  0.5f, 0.0f   // TL
    };
    unsigned int indices[] = {  //
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
    };

    unsigned int VBO;
    glGenBuffers(1, &VBO);

    unsigned int VAO;
    glGenVertexArrays(1, &VAO);

    unsigned int EBO;
    glGenBuffers(1, &EBO);

    //Binding the Vertex Array Object
    glBindVertexArray(VAO);

    //Bind the Vertex Buffer Object and copy vertices into it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Bind the Element Buffer Object and copy indices into it
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Setting the VOA attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

    //Main loop
    while(!sdlQuit){
        SDL_Delay(10);
        //Event handling
        eventHandle();


        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
//        glBindVertexArray(VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);


        SDL_GL_SwapWindow(window);
    }

    //SDL cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}