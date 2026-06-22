#ifndef SHADER_HPP
#define SHADER_HPP

#include <cstdlib>
#include <GL/glew.h>
#include <string>

class Shader{
    private:
        unsigned int program;                                                                   //our GL program that will be created; effectively an int-size list of bytes

        std::string loadFile(const std::string& path);                                                          //loading File helper function used to get our Shader programs into createExec... fx

        void createExecutableProgram(const std::string& vertexShader, const std::string& fragmentShader);             //creates an executable to run directly on GPU based off our shader programs

    public:
        Shader(const std::string vertShader, const std::string fragShader);                                           //Constructor which calls createExecutableProgram function to create GPU-ready shader
        ~Shader();                                                                              //Destructor which destroys our executable programs for GPU

        void useExecutableProgram();                                                            //Gives GL management over our GPU Program's state
};

#endif
