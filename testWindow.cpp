#ifndef TESTWINDOW_CPP
#define TESTWINDOW_CPP

#include <GL/glew.h>
#include "window.hpp"
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <stdexcept>

//#define GLEW_STATIC


const char* vertexSource =
	"#version 150\n"
	"in vec2 position;"
	"in vec3 color;"
	"out vec3 Color;"
	"void main() {"
	"	Color = c./olor;"
	"	gl_Position = vec4( position, 0.0, 1.0 );"
	"}";
const char* fragmentSource =
	"#version 150\n"
	"in vec3 Color;"
	"out vec4 outColor;"
	"void main() {"
	"	outColor = vec4( Color, 1.0 );"
	"}";

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
    using namespace std;
    using namespace sre;

    // GLFW init
    if( !glfwInit() )
        return 1;

    // create Window
    DefaultHints().apply();
    Window win = Window();
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
    GLuint vertexbuffer;
    glGenBuffers( 1, &vertexbuffer );
    glBindBuffer( GL_ARRAY_BUFFER, vertexbuffer );
    glBufferData( GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    glfwSetKeyCallback(win.getGLFWwindow(), key_callback);
    // main loop
    while( !glfwWindowShouldClose(win.getGLFWwindow()) )
    {
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

        win.swapBuffers();
        glfwPollEvents();

        // test various methods taking input from the user
        string title;
        cout<<"set title: ";
        cin>>title;
        win.setTitle(title);
        cout<<"set pos: ";
        ivec2 pos;
        cin>>pos.x>>pos.y;
        win.setPos(pos);
    }

    glfwTerminate();
    cerr<<"end";

    return 0;
}

#endif // TESTWINDOW_CPP
