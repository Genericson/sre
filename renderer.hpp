#ifndef RENDERER_H
#define RENDERER_H

#include <GL/glew.h>
#include <stdexcept>
#include <atomic>
#include "window.hpp"

//==namespace==//

namespace sre {

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

class Renderer
{
    GLuint vertexbuffer;
    int init();

    public:
        Window win;

        Renderer();
        virtual ~Renderer();
        void render();
    protected:
    private:

}; // Renderer

} // namespace sre

#endif // RENDERER_H
