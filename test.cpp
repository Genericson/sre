

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <iostream>
#include "window.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    using namespace sre;
    using namespace std;

    // Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();
#ifndef TESTWINDOW_CPP
#define TESTWINDOW_CPP


#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <atomic>
#include <sstream>
#include <memory>
#include "lexer.hpp"
#include "command.hpp"
#include "window.hpp"
#include "parser.hpp"
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
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose( win.load()->getGLFWwindow(), GL_TRUE );
    }
    if else (key == GLFW_KEY_EQUAL && action == GLFW_PRESS) {
    }
    if else (key == GLFW_KEY_MINUS && action == GLFW_PRESS) {
    }
}

void input();
void render(GLuint);

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
        render(vertexbuffer);
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

    // now test Command
    Type arg0 = Type("arg0"), arg1 = Type("arg1");
    CommandDef cmdDef = CommandDef("nothing");
    cmdDef.push(arg0);
    cmdDef.push(arg1);
    cmdDef.push(arg1);
    shared_ptr<CommandFunc> cmdFuncPtr = shared_ptr<CommandFunc>(new EmptyCommand() );
    cmdDef.setFunc(cmdFuncPtr);

    Command cmd = Command("nothing");
    cmd.push(arg0);
    cmd.push(arg1);
    cmd.push(arg1);


    cout<<(*cmdFuncPtr)(cmd)<<endl;

    cout<< "Is a command: " << (cmdDef == cmd) << endl;

    // create CommandMap and VariableMap for Lexer to use
    CommandMap cmdMap;

    VariableMap  varMap;
    // create lexer
    Lexer * lex = new Lexer("");
    // create and link parser to lexer
    Parser parser = Parser(*lex);

    do
    {
        getline(cin, str, '\n');
        //str.append("\n");
        //cout<<str;
        delete lex;
        lex = new Lexer(str);
        Token tok;
        do {
            tok = lex->next();
            cout<<"type: "<<tok.name()<<"  value: "<<tok.value<<std::endl;
        } while  (tok != Token::END_OF_INPUT && tok != Token::ERROR);
    } while (true);

    delete lex;

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

void render(GLuint vertexbuffer)
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

#endif // TESTWINDOW_CPP

    // Initialize GLFW
    if (!glfwInit())
        return -1;

    Monitor mon();
    WindowSettings winSet();
    FrameBufferSettings frameBufSet();
    ContextSettings contSet();

    //Window winDefault = Window();
    //Window winCustom = Window( 800, 600, "custom window");
    //winDefault.setActive();
    Window win = Window();

    //glfwSetKeyCallback ( window.getGLFWWindow(), key_callback );

    while( !win.windowShouldClose() )
    {
        win.swapBuffers();
        glfwPollEvents();
    }


    // Terminate GLFW
    glfwTerminate();
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
}
