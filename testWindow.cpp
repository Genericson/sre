#ifndef TESTWINDOW_CPP
#define TESTWINDOW_CPP

#include <GL/glew.h>
#include "window.hpp"
#include "compiler.hpp"
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <atomic>
#include <sstream>

//#define GLEW_STATIC


const char* vertexSource =
	"#version 150\n"
	"in vec2 position;"
	"in vec3 color;"
	"out vec3 Color;"
	"void main() {"
	"	Color = color;"
	"	gl_Position = vec4( position, 0.0, 1.0 );"
	"}";
const char* fragmentSource =
	"#version 150\n"
	"in vec3 Color;"
	"out vec4 outColor;"
	"void main() {"
	"	outColor = vec4( Color, 1.0 );"
	"}";

std::atomic< sre::Window *> win (nullptr);
// thread-safe output buffer for input
std::atomic< std::stringstream *> inputBuffer (nullptr);

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose( win.load()->getGLFWwindow(), GL_TRUE );
}

void input();
void render();

int main()
{
    using namespace std;
    using namespace sre;

    // initialize inputBuffer
    stringstream tempstr;
    inputBuffer.store(&tempstr);

    // GLFW init
    if( !glfwInit() )
        return 1;
    // Window::init()

    // create Window
    DefaultHints defhints = DefaultHints();
    defhints.apply();

    WindowHints winHints = WindowHints();
    winHints.resizable(1);
    winHints.visible(1);
    winHints.decorated(1);

    // test for Framebuffer methods
    FramebufferHints fbHints = FramebufferHints();
//    fbHints.redBits(1);
//    fbHints.greenBits(1);
//    fbHints.blueBits(1);
//    fbHints.alphaBits(1);
//    fbHints.depthBits(1);
//    fbHints.stencilBits(1);
//    fbHints.accumRedBits(1);
//    fbHints.accumGreenBits(1);
//    fbHints.accumBlueBits(1);
//    fbHints.accumAlphaBits(1);
//    fbHints.auxBuffers(1);
//    fbHints.samples(1);
//    fbHints.refreshRate(30);
//    fbHints.stereo(true);
//    fbHints.sRGBCapable(true);

    // test for ContextHints
    ContextHints cHints = ContextHints();
    //cHints.setAPIES();
    cHints.versionMajor(3);
    cHints.versionMinor(3);
    //cHints.forwardCompat(true);
    //cHints.debug(false);
    cHints.setProfileAny();

    Hints * hints;
    hints = &cHints;
    Window unatomicWin = Window( 640, 480, "OpenGL", *hints );
    win.store(&unatomicWin);
    if ( !win.load()->exists() )
    {
        throw runtime_error("Window creation failed.");
    }

    win.load()->makeActive();

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

    glfwSetKeyCallback(win.load()->getGLFWwindow(), key_callback);
    // main loop

    //create and initialize input thread
    thread textInputThread(input);
    textInputThread.detach();

    while( !win.load()->shouldClose() )
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

        win.load()->swapBuffers();

        // test various methods taking input from the user

        glfwPollEvents();
    }

    glfwTerminate();
    cerr<<"end";

    //garbage collection

    return 0;
}

void input()
{
    using namespace std;
    using namespace sre::console;
    istringstream inputbuf;
    string str = "";
    Token tok;
    do
    {
        getline(cin, str, '\n');
        str.append("\n");
        //cout<<str;
        Lexer lex = Lexer(str);
        tok = lex.next();
        cout<<"type: "<<tok.name()<<"  value: "<<tok.value<<std::endl;
        cout<<endl;
    } while (true);

//    string title;
//    glm::ivec2 pos;
//    glm::ivec2 size;
//
//    while (true)
//    {

//        cout<<"set title: ";
//        cout<<"title: ";
//        cin>>title;
//
//        win.load()->setTitle(title);
//
//        cout<<"set pos: ";
//        cin>>pos.x>>pos.y;
//        win.load()->setPos(pos);
//
//        cout<<"set size: ";
//        cin>>size.x>>size.y;
//        win.load()->setSize(size);
//
//        cout<<endl;
//
//        //spit out what the window is now
//        cout<<"Window Values..."<<endl;
//
//        pos = win.load()->getPos();
//        cout<<"pos: "<<pos.x<<" "<<pos.y<<endl;
//        size = win.load()->getSize();
//        cout<<"size: "<<size.x<<" "<<size.y<<endl;
//
//        cout<<endl;
//    }
}

void render()
{

}

#endif // TESTWINDOW_CPP
