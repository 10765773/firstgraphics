// This project is largely based on the work of Joey de Vries and his excellent publication LearnOpenGL,
// available online at https://learnopengl.com. Credit to him and others, including but not limited to:
//
// github.com/nothings and other contributors for their work on the stb_image.h library.

#include "glad.h"
#include <SDL.h>
#include <cmath>
#include <iostream>
#include "shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

const unsigned int G_SCREEN_WIDTH = 1080;
const unsigned int G_SCREEN_HEIGHT = 720;


SDL_Window *window;
SDL_GLContext glContext;
SDL_Event event;
bool sdlQuit;

void eventHandle() {
    SDL_PollEvent(&event);
    switch (event.type) {
        case SDL_QUIT:
            sdlQuit = true;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    sdlQuit = true;
            }
    }
}


int main(int argv, char **args) {
    sdlQuit = false;

    // SDL setup
    //Use OpenGL 3.3 core
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    //Initialise video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! SDL_Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    //Create SDL window
    window = SDL_CreateWindow("First Graphics",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              G_SCREEN_WIDTH,
                              G_SCREEN_HEIGHT,
                              SDL_WINDOW_OPENGL);
    if (window == nullptr) {
        std::cout << "Window could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    //Create OpenGL context
    glContext = SDL_GL_CreateContext(window);
    if (glContext == nullptr) {
        std::cout << "OpenGL context could not be created! SDL_Error:" << SDL_GetError() << std::endl;
        return -1;
    }

    //Initialize glad
    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    //Set OpenGL viewport size
    glViewport(0, 0, G_SCREEN_WIDTH, G_SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);

    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    //Binding the Vertex Array Object
    glBindVertexArray(VAO);

    //Bind the Vertex Buffer Object and copy vertices into it
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //Bind the Element Buffer Object and copy indices into it
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Setting the VOA attributes
    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    //Create an object of the shader class
    Shader myShader("../shaders/shader.vs", "../shaders/shader.fs");

    //Texture
    stbi_set_flip_vertically_on_load(true);
    int imgWidth, imgHeight, imgNrChannels;
    unsigned char *data = stbi_load("../img/container.jpg", &imgWidth, &imgHeight, &imgNrChannels, 0);
    unsigned int texture1, texture2;
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);
    // generate texture using loaded data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    data = stbi_load("../img/awesomeface.png", &imgWidth, &imgHeight, &imgNrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    myShader.use();
    myShader.setInt("texture1",0);
    myShader.setInt("texture2",1);


    //Main loop
    while (!sdlQuit) {
        SDL_Delay(10);
        //Event handling
        eventHandle();

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        myShader.use();

        //3D Stuff
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float) G_SCREEN_HEIGHT / (float) G_SCREEN_HEIGHT, 0.1f,
                                      100.0f);

        unsigned int modelLoc = glGetUniformLocation(myShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(myShader.ID, "view");

        model = glm::rotate(model, (float)SDL_GetTicks()/1000 * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));


        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);


        myShader.setMat4("projection", projection);

        // render container
        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 36);

        SDL_GL_SwapWindow(window);
    }
    uint32_t time = SDL_GetTicks();
    double timeinsecs = time / 1000.0;
    std::cout << "Time in ms: " << time << "\nTime in s: " << timeinsecs << std::endl;

    //SDL cleanup
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}