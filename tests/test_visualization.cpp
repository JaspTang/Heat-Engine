#include "Grid.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"

#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

int main() {
    /*  Initialize renderer */
    Renderer renderer;

    bool running = true;

    while (running) {
        /*  Start an SDL_event  */
        SDL_event e;

        while(SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }
        
        /*  Render  */
        renderer.render();  
    }

    return 0;
}
