#include <hints.hpp>

namespace sre
{

    // MapHints
    void MapHints::applyHint ( const Hints::KEY & key, const int & val )
    {
        // find GLFW equivalent of key and use that to call glfwWindowHint
        int _key;
        int _val = val;

        switch (key)
        {
        case RESIZABLE:
            _key = GLFW_RESIZABLE; break;
        case VISIBLE:
            _key = GLFW_VISIBLE; break;
        case DECORATED:
            _key = GLFW_DECORATED; break;
        case RED_BITS:
            _key = GLFW_RED_BITS; break;
        case GREEN_BITS:
            _key = GLFW_GREEN_BITS; break;
        case BLUE_BITS:
            _key = GLFW_BLUE_BITS; break;
        case ALPHA_BITS:
            _key = GLFW_ALPHA_BITS; break;
        case DEPTH_BITS:
            _key = GLFW_DEPTH_BITS; break;
        case STENCIL_BITS:
            _key = GLFW_STENCIL_BITS; break;
        case ACCUM_RED_BITS:
            _key = GLFW_ACCUM_RED_BITS; break;
        case ACCUM_GREEN_BITS:
            _key = GLFW_ACCUM_GREEN_BITS; break;
        case ACCUM_BLUE_BITS:
            _key = GLFW_ACCUM_BLUE_BITS; break;
        case ACCUM_ALPHA_BITS:
            _key = GLFW_ACCUM_ALPHA_BITS; break;
        case AUX_BUFFERS:
            _key = GLFW_AUX_BUFFERS; break;
        case SAMPLES:
            _key = GLFW_SAMPLES; break;
        case REFRESH_RATE:
            _key = GLFW_REFRESH_RATE; break;
        case STEREO:
            _key = GLFW_STEREO; break;
        case SRGB_CAPABLE:
            _key = GLFW_SRGB_CAPABLE; break;
        case CLIENT_API:
            _key = GLFW_CLIENT_API;
            switch(val)
            {
            case OPENGL_API:
                _val = GLFW_OPENGL_API; break;
            case OPENGL_ES_API:
                _val = GLFW_OPENGL_ES_API; break;
            default:
                std::cerr<<"Unsupported OpenGL API setting";
            }
            break;
        case VERSION_MAJOR:
            _key = GLFW_VERSION_MAJOR; break;
        case VERSION_MINOR:
            _key = GLFW_VERSION_MINOR; break;
        case CONTEXT_ROBUSTNESS:
            _key = GLFW_CONTEXT_ROBUSTNESS; break;
            switch(val)
            {
            case NO_ROBUSTNESS:
                _val = GLFW_NO_ROBUSTNESS; break;
            case NO_RESET_NOTIFICATION:
                _val = GLFW_NO_RESET_NOTIFICATION; break;
            case LOSE_CONTEXT_ON_RESET:
                _val = LOSE_CONTEXT_ON_RESET; break;
            default:
                std::cerr<<"Unsupported robustness setting";
            }
        case OPENGL_FORWARD_COMPAT:
            _key = GLFW_OPENGL_FORWARD_COMPAT; break;
        case OPENGL_DEBUG:
            _key = GLFW_OPENGL_DEBUG_CONTEXT; break;
        case OPENGL_PROFILE:
            _key = GLFW_OPENGL_PROFILE; break;
            switch(val)
            {
            case ANY:
                _val = GLFW_OPENGL_ANY_PROFILE; break;
            case OPENGL_COMPAT:
                _val = GLFW_OPENGL_COMPAT_PROFILE; break;
            case OPENGL_CORE:
                _val = GLFW_OPENGL_CORE_PROFILE; break;
            default:
                std::cerr<<"Unsupported OpenGL profile";
            }
        default:
            std::cerr<<"Unsupported key value for applyHint()";
            break; //this should never happen!!!
        }

        // Now apply hint using GLFW
        glfwWindowHint( _key, _val);

    }
    void MapHints::apply() const
    {
        // apply each hint;
        for( std::pair<Hints::KEY, int>  hint : *this)
        {
            applyHint( hint.first, hint.second );
        }
    }

    /// Default GLFW hint settings
    /// Equivalent to calling glfwDefaultWindowHints();
    void DefaultHints::apply() const
    {
        glfwDefaultWindowHints();
    }

    void WindowHints::apply() const
    {
        glfwWindowHint( GLFW_RESIZABLE, _resizable );
        glfwWindowHint( GLFW_VISIBLE, _visible );
        glfwWindowHint( GLFW_DECORATED, _decorated );
    }

    void FramebufferHints::apply() const
    {
        glfwWindowHint( GLFW_RED_BITS, _redBits );
        glfwWindowHint( GLFW_BLUE_BITS, _blueBits );
        glfwWindowHint( GLFW_GREEN_BITS, _greenBits );
        glfwWindowHint( GLFW_ALPHA_BITS, _alphaBits );
        glfwWindowHint( GLFW_DEPTH_BITS, _depthBits );
        glfwWindowHint( GLFW_STENCIL_BITS, _stencilBits );
        glfwWindowHint( GLFW_ACCUM_RED_BITS, _accumRedBits );
        glfwWindowHint( GLFW_ACCUM_GREEN_BITS, _accumGreenBits );
        glfwWindowHint( GLFW_ACCUM_BLUE_BITS, _accumBlueBits );
        glfwWindowHint( GLFW_ACCUM_ALPHA_BITS, _accumAlphaBits );
        glfwWindowHint( GLFW_AUX_BUFFERS, _auxBuffers );
        glfwWindowHint( GLFW_SAMPLES, _samples );
        glfwWindowHint( GLFW_REFRESH_RATE, _refreshRate );
        glfwWindowHint( GLFW_STEREO, _stereo );
        glfwWindowHint( GLFW_SRGB_CAPABLE, _sRGBCapable );
    }

} // namespace sre
