/*  Renderer
 *
 *  Shader - now we have our shader program, it has been attached to the program and we are ready to use the shader program
 *
 *  The Renderer will use the shader program and this class serves two purposes:
 *  1. Use OpenGL to create a context for the GPU
 *  2. Attach the SDL window to the context
 *  3. Initialize Vertex Buffer Object and Vertex Array Object
 *  4. Define VBO and VAO
 *
 */

#include "Renderer.hpp"
#include "Shader.hpp"
#include "Grid.hpp"

/*  We are using SDL for window management and OpenGL for GPU management (mainly memory and context management) */
#include <SDL2/SDL.h>
#include <GL/glew.h>

/* Used for input and such (functionality) */
#include <iostream>
#include <cstdlib>
#include <memory>

/*  Constructor: Call helper functions to enable GL library with GPU, initialize our context and window and define our vao, vbo buffers */
Renderer::Renderer() {
    initializeContextandWindow();
    initializeOpenGL();
    shader = make_unique<Shader>("shaders/point.vert", "shaders/heat.frag");
    initializeandDefineBuffers();
}

/*  Destructor: delete our context and destroy our window   */
Renderer::~Renderer() {
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

/*  initializeOpenGL
 *  
 *  Initializing OpenGL allows us to access our GPU's GL & GLEW Functions from the driver
 */
void Renderer::initializeOpenGL() {
    glewExperimental = GL_TRUE;

    glewInit();
}

/*  initializeContextandWindow
 *
 *  This is all about how we manage the GPU from here on in. Our GPU will have a context - an "art studio" - a place to manage all the resources needed
 *  We created our window via SDL and we need to attach that window to the contxt so the GPU can perform the calculations and actually draw on the canvas 
 *  (thru ultimately the fragment shader)
 *
 */
void Renderer::initializeContextandWindow() {
    /*  Start a new SDL instance    */
    SDL_Init(SDL_INIT_VIDEO);
    
    /*  Define what version of OpenGL we will use   */
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    /*  Create our window - titled Heat Engine, centered, 800 x 600 pixels, usable with OpenGL context  */
    window = SDL_CreateWindow("Heat Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
    
    /*  Create our context - attach it to the window, so now our window has GPU resources attached to it    */
    context = SDL_GL_CreateContext(window);
}

/*  initializeandDefineBuffers()
 *
 *  Now that we have our context and window, we have one last thing to cover
 *  We have to manage our GPU's memory - specifically, the vertex array objects (VAO) and the vertex buffer objects (VBO)
 *  VBO: stores vertex data [0 1 2] - 1 vertex w/ 2 attributes (x, y) & temp: [(x, y), temp]
 *      - This buffer stores all the vertices' data
 *  VAO: stores the instructions for interpreting our VBO data -- it is NOT actual vertex data
 *      - if we store [(x,y), temp], VAO says attribute0 is 2 floats and attribute1 is 1 float
 *      - good for distinctions of [1,2,3] and [(1,2),3]
 *
 *  What is Binding?
 *  Binding is basically saying we want x buffer to be affected - the target buffer to be modified
 *  In this case, we are saying that we want vbo to be modified, and we want our point data to be uploaded there
 */
void Renderer::initializeandDefineBuffers() {
    /*  OUR DATA    */
    float point[] = {0.0f, 0.0f, 1.0f};
    


    /*  VBO - VERTEX BUFFER OBJECT - OUR ACTUAL DATA    */

    /*  INITIALIZE (1, into vbo) */
    glGenBuffers(1, &vbo);
    /*  BIND    */
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    /*  UPLOAD  */
    glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);
    


    /*  VAO - VERTEX ARRAY OBJECT - OUR LAYOUT INFORMATION  */

    /*  INITIALIZE  */
    glGenVertexArrays(1, &vao);
    /*  BIND    */
    glBindVertexArray(vao);
    /*  LAYOUT  */
    /*  Initialize and Define: Attribute 0: 2 floats, stride = 3 floats, starts at offset 0    */
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    /*  Initialize and Define: Attribute 1: 1 float, stride = 3 floats, starts at offset 2 floats (after the second float)  */
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

/*  Render
 *
 *  THIS WILL BE OUR FUNCTION THAT WILL RUN IN THE RUNNING LOOP.
 *  Every time we render, we should redefine what data is expected and in what format and then redraw (i.e. update our context) and then 
 *  update our window
 */
void Renderer::render() {
    /*  Effectively Clears the screen   */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /*  Calls the shader class to take the input data and convert that to a point on the screen with a color    */
    shader->useExecutableProgram();

    /*  Make sure GL knows the configuration of our vbo's again */
    glBindVertexArray(vao);
    /*  What data are we expecting and how we will we draw it - "mode"; first, count    */
    glDrawArrays(GL_POINTS, 0, 1);
    /*  Update our window from our context  */
    SDL_GL_SwapWindow(window);
}
