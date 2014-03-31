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
//#include "lexer.hpp"
//#include "command.hpp"
#include "window.hpp"
//#include "parser.hpp"
#include "renderer.hpp"
//#define GLEW_STATIC

int main()
{
    using namespace std;
    using namespace sre;

    Renderer ren = Renderer();

    while (!ren.win.shouldClose()) {
        ren.render();
    }

    glfwTerminate();
    cerr<<"end";

    //garbage collection

    return 0;
}

/*void input()
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
}*/

/*void render(GLuint vertexbuffer)
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
}*/

#endif // TESTWINDOW_CPP
