#include "Shader.hpp"

/*  Libraries for Functionality - GLEW GL Library Extension (for specific Function Calls)   */
#include <cstdlib>
#include <string>
#include <GL/glew.h>
#include <fstream>
#include <sstream>

/*  Shader File
 *
 *  Our vertex and fragment shader (as well as other shaders) are written in GLSL in the shader repo
 *  The GLSL Programs define how the GPU performs math to convert our temperature data --> pixel color * pos
 *
 *  Now: use openGL to compile, link, and package our GLSL Programs into GPU-ready programs to execute on hardwarer
 *  
 *  1. Load Shader files; 2. Compile Shaders; 3. Link Shaders; 4. Package Shaders;
 *
 *  As a class, this will be used by our renderer (initializes context, prepares context, initializes & prepares gpu memory
 */

using namespace std;

/*  Load File: loads the GLSL Programs from file path   */
string Shader::loadFile(const string& path) {
    ifstream file(path);
    stringstream buffer;

    buffer << file.rdbuf();

    return buffer.str();                            //TODO
}

/*  Constructor: when we create a Shader Object, we want it to package our current Shaders, so we call createProgram to do this   */
Shader::Shader(const string vertShader, const string fragShader) {
    /*  Everytime we create a new Shader object, we want to do this, so that's why we call in our constructor and not independently
     *  Also, we want the function outside of the constructor to be able to be called on its own too
     */
    createExecutableProgram(loadFile(vertShader), loadFile(fragShader));
}

/*  createExecutableProgram
 *
 *  We will create an executable program for our GPU's hardware
 *  We take our shader programs and convert it to a single executable that can run on our GPU
 *  
 *  Notice: OpenGL manages the programs that execute directly on the GPU
 *
 *  Steps:
 *  1. import Shader Programs & initialize GL Shader Programs (ones managed by GL)
 *  2. compile Shader Programs (vs, fs = temporary compiled shader programs)
 *  3. initialize GL GPU Program
 *  4. Attach Shaders to this GL GPU Program
 *  5. Link Shaders to the Program
 *      - creates executable that'll run on the vertex processor and fragment processor
 *      - Also considers othe questions such as "Do in and out data types match each other?"
 *  6. delete our temporary compiled-shader programs
 */

void Shader::createExecutableProgram(const string& vertexShader, const string& fragmentShader) {
    //1.
    /* Initialize new Shader Objects (1 for vertex shader, 1 for fragment shader) */
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    
    /*  NOTE: glCompileShader wants to compile the SOURCE CODE STRINGS as defined by each shader object,
     *  so let's get this (we convert it to a string in C: contiguous chars terminated by null character
     */
    const char* vsSRC = vertexShader.c_str();
    const char* fsSRC = fragmentShader.c_str();

    /*  NOTE: now that we have both new shader objects and our imported shaders (written in GLSL), 
     *  we need the shader programs we imported to be the source code of those shader objects - 
     *  this is what glCompile expects
     *  
     *  So, let's replace the source code of each Shader object with vsSRC (our GLSL instructions) that have been converted to a string
     *  so function works correctly. Replace vs src code with vsSRC GLSL program, where it is 1 long string null terminated
     */
    glShaderSource(vs, 1, &vsSRC, nullptr);
    glShaderSource(fs, 1, &fsSRC, nullptr);
    
    //2.
    glCompileShader(vs);
    glCompileShader(fs);

    //3.
    program = glCreateProgram();

    //4.
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    //5.
    glLinkProgram(program);

    //6.
    glDeleteShader(vs);
    glDeleteShader(fs);
}

/*  Destructor: Used the provided GL function to free the memory taken up by our created Program Object and 
 *  invalidate the name of our Program Object to effectively destroy Program
 */  
Shader::~Shader() {
    glDeleteProgram(program);
}

/*  useExecutable Program()
 *
 *  Per GL's library, take the program that we have created and is prepared for executable and use it
 *  GL will manage the program from hereon
 */
void Shader::useExecutableProgram() {
    glUseProgram(program);
}



