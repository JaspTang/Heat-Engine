#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "Shader.hpp"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include <cstdlib>
#include <string>

#include <memory>

class Renderer {
    public:
        Renderer();                         /*  Constructor: initialize gl functions, initialize context and window, initialize buffers  */

        ~Renderer();                        /*  Destructor: delete and destroy our context and window    */

        void render();                      /*  Execute our shader and use the shader values to update the window   */

    private:
        /*  Create our SDL window and also create a context for our GPU to manage   */
        SDL_Window* window;
        SDL_GLContext context;
        
        /*  Create the memory management through GL vertex objects  */
        unsigned int vao;
        unsigned int vbo;

        /* Helper Functions */
        void initializeOpenGL();
        void initializeContextandWindow();
        void initializeandDefineBuffers();
        
        /*  The specific shader our Renderer will be using  */
        std::unique_ptr<Shader> shader;
};

#endif
