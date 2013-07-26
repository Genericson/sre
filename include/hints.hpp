#ifndef HINTS_HPP
#define HINTS_HPP

#include <GLFW/glfw3.h>

namespace sre
{
    /** Represents a set of GLFW Hints **/
    class Hints
    {
    public:
        /** Applies GLFW/OpenGL settings for window, its context, and framebuffers **/
        virtual void apply() =0;
    };

    class DefaultHints : public Hints
    {
        public:
        void apply();
    };

} // namespace sre

#endif // HINTS_HPP
