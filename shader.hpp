#ifndef SHADER_HPP
#define SHADER_HPP

namespace sre {

/// a basic hard-codded vertex shader
static const char* vertexSource =
        "#version 330\n"
        "layout(location = 0) in vec4 vPosition;\n"
        "void main() {"
        "	gl_Position = vPosition;\n"
        "}";
/// a basic hard-coded fragment shader
static const char* fragmentSource =
        "#version 33.\n"
        "out vec4 fColor;\n"
        "void main() {\n"
        "	fColor = vec4( 1.0, 1.0, 1.0, 1.0 );\n"
        "}";

class Shader
{
public:
    /** Default constructor */
    Shader ();
    /** Default destructor */
    virtual ~Shader ();
    GLuint getId () { return this->shader; }
protected:
    GLuint shader; ///< the OpenGL id of the shader.
    const char* source; ///< the shader source code c string
    const int logLength = 256;
    std::string errorLog;
private:

};

class VertexShader : public Shader
{
public:
    VertexShader();
};

class FragmentShader : public Shader
{
public:
    FragmentShader();
};

//--- Shader Program ---//

class ShaderProgram
{
public:
    ShaderProgram();
    ~ShaderProgram();
    void attach (Shader shader);
private:
    GLuint program;
};

} //namespace sre

#endif // SHADER_HPP


