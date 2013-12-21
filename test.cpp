

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
