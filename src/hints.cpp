#include <hints.hpp>

namespace sre
{

    /// Default GLFW hint settings
    /// Equivalent to calling glfwDefaultWindowHints();
    void DefaultHints::apply()
    {
        glfwDefaultWindowHints();
    }

} // namespace sre
