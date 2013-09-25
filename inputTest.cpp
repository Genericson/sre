

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <iostream>
#include "input.hpp"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Window;

int main()
{
    //using namespace sre;
    using namespace std;

    // Initialize GLEW
	glewExperimental = GL_TRUE;
	glewInit();

    // Initialize GLFW
    if ( !glfwInit() )
        return -1;

    GLFWwindow * win = glfwCreateWindow( 640, 480, "test", NULL, NULL );

    //Window winDefault = Window();
    //Window winCustom = Window( 800, 600, "custom window");
    //winDefault.setActive();
    //Window win = Window();

    //glfwSetKeyCallback ( window.getGLFWWindow(), key_callback );

    while( glfwWindowShouldClose(win) )
    {
        glfwSwapBuffers( win );
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

class Window
{
    GLFWwindow * window;

    Window( int width, int height, string title, Monitor monitor, Window share);
    Window( )
};
