#include "renderer.hpp"
#include "window.hpp"
#include "shader.hpp"

//==namespace==//
namespace sre {

Renderer::Renderer()
{
    init();
} // ctor

Renderer::~Renderer()
{
    //dtor
} // dtor

int Renderer::init()
{
    //ctor
    using namespace std;
    using namespace sre;

    // GLFW init
    if( !glfwInit() )
        return 1;

    Hints * defaultHints = new DefaultHints();
    win = Window(640, 480, "OpenGL", *defaultHints);


    if ( !win.exists() )
    {
        throw runtime_error("Window creation failed.");
    }

    win.makeActive();

    // GLEW init
    glewExperimental = GL_TRUE; // include all the fancy features!
    if( glewInit() != GLEW_OK )
        throw runtime_error("GLEW initialization failed.");

    // vao
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    // vertex array
    static const GLfloat g_vertex_buffer_data[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };

    // vertexbuffer

    glGenBuffers( 1, &vertexbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // shader
    VertexShader vertexShader = VertexShader();
    ShaderProgram shaderProgram = ShaderProgram();
    shaderProgram.attach(vertexShader);

    glfwSetKeyCallback(win.getGLFWwindow(), key_callback);
    return 0;
} // init()

void Renderer::render() {
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glVertexAttribPointer(
       0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalized?
       0,                  // stride
       (void*)0            // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle

    glDisableVertexAttribArray(0);

    this->win.swapBuffers();

    // test various methods taking input from the user

    glfwPollEvents();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GL_TRUE);
}

} // namespace sre
