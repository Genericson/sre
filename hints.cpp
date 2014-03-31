#include "hints.hpp"

namespace sre
{

    //== WindowAttribs ==//
    /** \class WindowAttribs
     *  \brief A class for representing window attributes. */

    /** \enum WindowAttribs::KEY
     *  \brief An enumeration of all valid window attributes. */

    /** This Function converts a WindowAttribs::KEY and value to the GLFW equivalents
     *  \param[in] attrib The WindowAttribs::KEY to convert.
     *  \param[in] val The value to convert. This is identical unless the `attrib` has an associated enumeration
     *  \param[out] attribGLFW Where to save the GLFW attribute identifier.
     *  \param[out] valGLFW Where to save the GLFW value equivalent.
     *  \sa \ref window_hints "GLFW window creation hints", \ref window_attribs "GLFW window attributes"*/
    void WindowAttribs::getGLFWattrib ( const WindowAttribs::KEY & attrib, const int & val, int & attribGLFW, int & valGLFW )
    {
         // find GLFW equivalent of key and value
        int _val = val;
        int _key;

        switch (attrib)
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
                std::cerr<<"Unsupported OpenGL API setting"<<std::endl;
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
                std::cerr<<"Unsupported robustness setting\n"<<std::endl;
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
                std::cerr<<"Unsupported OpenGL profile"<<std::endl;
            }
        default:
            std::cerr<<"Unsupported key value for applyHint()";
            break; //this should never happen!!!
        }

        attribGLFW = _key;
        valGLFW = _val;
    } // WindowAttribs::getGLFWattrib
    //^ WindowAttribs

    //== Hints ==//
    /** \class Hints
     *  \brief An interface representing a collection of hints for a window \sa \ref window_hints_values "GLFW window hints" */

    /** \fn virtual void Hints::apply() const =0
     *  \brief A function that applies GLFW/OpenGL settings for a window, its context and framebuffers \sa glfwWindowHint */
    //^ Hints

    //== HintsMap ==//
    /** \class HintsMap
     *  \brief A container for hints */

    /** Applies the given hint
     *  \param[in] key The name of the hint to apply.
     *  \parma[in] val The value to apply for the hint.
     *  \sa getGLFWattrib, \ref window_hints_values "GLFW window hints" */
    void HintsMap::applyHint ( const WindowAttribs::KEY & key, const int & val )
    {
        // find GLFW equivalent of key and use that to call glfwWindowHint
        int _key;
        int _val;
        getGLFWattrib( key, val, _key, _val);

        // TEMP
        std::cerr<<"key: "<<key<<"  val: "<<val<<std::endl;
        // Now apply hint using GLFW
        glfwWindowHint( _key, _val);

    }
    /** Applies all hints that this contains.
     *  \note All hints not contained in this are unaffected and retain their current values */
    void HintsMap::apply () const
    {
        // apply each hint;
        for( std::pair<Hints::KEY, int>  hint : *this)
        {
            applyHint( hint.first, hint.second );
        }
    }
    //^ HintsMap

    //== DefaultHints ==//
    /** \class DefaultHints
     *  \brief A class representing the default GLFW hint settings */

    /** Applies the defult hints.
     *  \note The function is equivalent to calling glfwDefaultWindowHints(); */
    void DefaultHints::apply() const
    {
        glfwDefaultWindowHints();
    }
    //^ DefaultHints

    //== WindowHints ==//
    /** \class WindowHints
     *  \brief A class containing all window-related hints. */
        //// ctor ////
    /** Adds window-related hints with default values. */
    WindowHints::WindowHints()
    {
        // set default values
        resizable(true);
        visible(true);
        decorated(true);
    }
    //^ WindowHints

    //== FramebufferHints ==//
    /** \class FramebufferHints
     *  \brief A class containing all framebuffer-related hints. */
        //// ctor ////
    /** This function adds framebuffer-related hints with default values. */
    FramebufferHints::FramebufferHints()
    {
        // set default values
        redBits(8);
        greenBits(8);
        blueBits(8);
        alphaBits(8);
        depthBits(24);
        stencilBits(8);
        accumRedBits(0);
        accumGreenBits(0);
        accumBlueBits(0);
        accumAlphaBits(0);
        auxBuffers(0);
        samples(0);
        refreshRate(0);
        stereo(false);
        sRGBCapable(false);
    }
    //^ FramebufferHints

    //== ContextHints ==//
    /** \class ContextHints
     *  \brief A class containing all context-related hints. */
        //// ctor ////
    /** Adds context-related hints with default values. */
    ContextHints::ContextHints()
    {
        // set default values
        setAPIGL();
        versionMajor(1);
        versionMinor(1);
        setNoRobustness();
        forwardCompat(false);
        debug(false);
        setProfileAny();
    }
    //^ ContextHints

} // namespace sre
