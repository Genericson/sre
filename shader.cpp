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
    glDeleteShader(this->shader);
}

/** \class VertexShader
 */

VertexShader::VertexShader() {
    //Create a vertex shader
    GLuint shader = glCreateShader(GL_VERTEX_SHADER);
        // if gl shader object allocation was unsuccessful, stop and send notification
        // to error console
    if (shader == 0) {
        std::cerr<<"Vertex shader creation failed!\n";
    }
    else {
            // save shader id
        this->shader = shader;
            //Shader sourcecode (default)
        this->source = vertexSource;
        glShaderSource(shader, 1, &source, NULL);
            //Attempt to compile the shader...
        glCompileShader(shader);
            //get compilation status
        GLint * param;
        glGetShaderiv(shader, GL_COMPILE_STATUS, param);
            // if compilation is unsuccessfull:
        if(param) {
                //print out log info
            char * infoLog = new char[logLength];
            glGetShaderInfoLog( shader, logLength - 1, NULL, infoLog );
            // copy logLength characters of shader's error log is saved
            errorLog += infoLog;
            std::cerr<<errorLog;
        } else {  // compilation is successful




        }
    }
} // VertexShader

/** \class FragmentShader
 *  ToDo
 */

/** \class ShaderProgram
 *  ToDo
 */

ShaderProgram::ShaderProgram() {
        //create shader program;
    GLuint program = glCreateProgram();
    this->program = program;
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(this->program);
}
void ShaderProgram::attach(Shader shader) {
    glAttachShader(this->program, shader.getId());
}

} // namespace sre
