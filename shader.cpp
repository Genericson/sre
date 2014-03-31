#include <GL/glew.h>
#include <iostream>
#include "shader.hpp"

namespace sre {

/** \class Shader
 *  \brief A class representing shader code
 */

/**
 *
 */
Shader::Shader( )
{

}

Shader::~Shader()
{
    //dtor
}

/** \class VertexShader
 */

VertexShader::VertexShader() {
    //Create a vertex shader
    GLuint sh = glCreateShader(GL_VERTEX_SHADER);
    if (sh == 0) {
        std::cerr<<"Vertex shader creation failed!\n";
    }
    else {
            //Shader sourcecode (default)
        this->source = vertexSource;
        glShaderSource(sh, 1, &source, NULL);
            //Attempt to compile the shader...
        glCompileShader(sh);
            //get compilation status
        GLint * param;
        glGetShaderiv(sh, GL_COMPILE_STATUS, param);
            // if compilation is unsuccessfull:
        if(param) {
                //print out log info
            char * infoLog = new char[256];
            glGetShaderInfoLog(sh, 255, NULL, infoLog);
            std::cerr<<infoLog<<std::endl;
        }
    }
}

/** \class FragmentShader
 */

/** \class ShaderProgram
 *
 */

} // namespace shader
