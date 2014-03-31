#ifndef SHADER_HPP
#define SHADER_HPP

namespace sre {

static const char* vertexSource =
        "#version 150\n"
        "in vec2 position;\n"
        "in vec3 color;\n"
        "out vec3 Color;\n"
        "void main() {\n"
        "	Color = position.xxy;\n"
        "	gl_Position = vec4( position, 0.0, 1.0 );\n"
        "}";
static const char* fragmentSource =
        "#version 150\n"
        "in vec3 Color;\n"
        "out vec4 outColor;\n"
        "void main() {\n"
        "	outColor = vec4( Color, 1.0 );\n"
        "}";

class Shader
{
public:
    /** Default constructor */
    Shader();
    /** Default destructor */
    virtual ~Shader();
protected:
    GLuint shader;
    const char* source;
    unsigned int id;
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

} //namespace sre

#endif // SHADER_HPP


