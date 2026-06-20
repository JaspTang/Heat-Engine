#include "Renderer.hpp"
#include "Grid.hpp"

/*  Import SDL * OpenGL Tools
 *  SDL: window, peripheral access & interactions
 *      - Also creates OpenGL Context TODO
 *  OpenGL GLEW: TODO
 *
 */

#include <SDL2/SDL.h>
#include <GL/glew.h>

/* Used for input and such (functionality) */
#include <iostream>
#include <cstdlib>

using namespace std;

/*  Vertex Shader:
 *  
 *  Converts our temperature list/buffer to positions in our context TODO
 *  #version 330 core - GLSL version 3.3 & core profile (modern OpenGL only) TODO
 *  
 *  We are setting up how our vectors wil look like for the GPU
 *  //layout(location = 0) in vec2 pos;
 *  vec2 = (x,y)                                            TODO
 *
 *  We are taking in temperature as another vector and outputting it:
 *
 *
 */

const char* vertexShaderSrc = R"(
#version 330 core

layout(location = 0) in vec2 pos;
layout(location = 1) in float temp;

out float vTemp;

void main() {
    vTemp = temp;
    gl_Position = vec4(pos, 0.0, 1.0);
    gl_PointSize = 10.0
}
)";

const char* fragmentSharderSrc = R"(
#version 330 core

in float vTemp;
out vec4 color;

void main() {
    vec3 cold = vec3(0.0, 0.0, 1.0);
    vec3 hot = vec3(1.0, 0.0, 0.0);

    vec3 finalColor = mix(cold, hot, vTemp);

    color = vec4(finalColor, 1.0);
}
)";

/* THIS SHOULD GO INTO THE SHADER PORTION */
GLuint createProgram() {
    GLuint vs = compileShader(GL_VERTEX_SHADER, vertexShaderSrc);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, framentShaderSrc);

    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

//TODO: Remove
int main() {

    //RENDERER: CREATE CONTEXT, CREATE WINDOW, ATTACH CONTEXT TO WINDOW, DEFINE CONTEXT WITH VAO AND VBO (MEMORY MANAGEMENT), DISPLAY SCREEN

    SDL_Init(SDL_INIT_VIDEO); //RENDERER

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3); //RENDERER
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3); //RENDERER
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); //RENDERER

    //edge case 1: TODO
    //if (SDL_Init(SDL_INIT_VIDEO) < 0) {cerr << "SDL init failed\n"; return 1;}

    SDL_Window* window = SDL_CreateWindow("Heat GLSL - One Point", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1000, 800, SDL_WINDOW_OPENGL); //RENDERER

    //if (!window) {cerr << "Window Failed\n"; return 1;}
    
    SDL_GLContext context = SDL_GL_CreateContext(window); //RENDERER

    glewExperiment = GL_TRUE; //enable GL Functions from the GPU Driver //RENDERER
    glewInit();                                                         //RENDERER

    GLuint program = createProgram();                                   //RENDERER

    float data[] = {0.0f, 0.0f, 1.0f};                                  //RENDERER

    GLuint vao, vbo;                                                    //RENDERER

    glGenVertexArrays(1, &vao);                                         //RENDERER
    glGenBuffers(1, &vbo);                                              //RENDERER

    glBindVertexArray(vao);                                             //RENDERER

    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                 //RENDERER
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);  //RENDERER

    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2 * sizeof(float))); //RENDERER
    glEnableVertexAttribArray(1);                                                                   //RENDERER
    
    //WILL THIS BE MAIN?

    bool running = true;

    while (running) {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = false;
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glBindVertexArray(vao);
        
        glDrawArrays(GL_POINTS, 0, 1);

        SDL_GL_SwapWindow(window);
    }

    //SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
