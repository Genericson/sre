#include "window.hpp"

namespace sre
{
    //////////////
    //  Window
    //
    //////////////

    // constructors
    Window::Window ( GLFWwindow * window )
    {
        this->window = window;
    }
    Window::Window ( const int width, const int height,
                    const std::string & title,
                    const Hints & hints,
                    const Monitor & monitor,
                    const Window & share )
    {
        hints.apply();
        this->window = glfwCreateWindow( width, height,
                                       title.c_str(),
                                       monitor.getGLFWMonitor(),
                                       share.window );
    }
    // get methods
    GLFWwindow * Window::getGLFWwindow()
    {
        return this->window;
    }
    ivec2 Window::getFramebufferSize() const
    {
            ivec2 size;
            glfwGetFramebufferSize( this->window, &size.x, &size.y );
            return size;
    }
    /** Returns window's position in pixels
        \param[out] a vector holding the x and y coordinates of the window in pixels
        \sa setPos(), glfwGetWindowPos()
    */
    ivec2 Window::getPos () const
    {
        ivec2 pos;
        glfwGetWindowPos( this->window, &pos.x, &pos.y );
        return pos;
    }
    /** Returns window's size in pixels
        \param[out] a vector holding the width and height of the window in pixels
        \sa setSize(), glfwGetWindowPos()
    */
    ivec2 Window::getSize () const
    {
        ivec2 size;
        glfwGetWindowSize( this->window, &size.x, &size.y );
        return size;
    }
    /** Returns true if window was created successfully
        \param[out] true if window exists, false otherwise
        \sa Window(), glfwCreateWindow()
    */
    bool Window::exists () const
    {
        return (window != nullptr);
    }
    /** checks if window's "should close" flag is set
        \param[out] -GL_TRUE if window should close
                    -GL_FALSE if windw should remain open
    */
    int Window::shouldClose () const
    {
        return glfwWindowShouldClose( this->window );
    }

    // set
    /** Sets window's title
        \param[in] title new title
        \sa getTitle(), glfwGetWindowTitle()
    */
    void Window::setTitle ( std::string title )
    {
        glfwSetWindowTitle( this->window, title.c_str() );
    }
    /** Sets window's position
        \param[in] width x screen coordinate
        \param[in] height y screen coordinate
        \sa getPos(), glfwSetWindowPos()
    */
    void Window::setPos ( int width, int height )
    {
        glfwSetWindowPos( this->window, width, height );
    }
    /** Sets window's position
        \param[in] pos vector of x and y screen coordinates
        \sa getPos(), glfwSetWindowPos()
    */
    void Window::setPos ( ivec2 pos )
    {
        glfwSetWindowPos( this->window, pos.x, pos.y );
    }
    /** Sets window's size in pixels
        \param[in] xSize width in pixels
        \param[in] ySize height in pixels
        \sa getPos(), glfwSetWindowSize()
    */
    void Window::setSize ( int xSize, int ySize )
    {
        glfwSetWindowSize( this->window, xSize, ySize );
    }
    /** Sets window's size in pixels
        \param[in] size size in pixels
        \sa getPos(), glfwSetWindowSize()
    */
    void Window::setSize ( ivec2 size )
    {
        glfwSetWindowSize( this->window, size.x, size.y );
    }

    // set command
    void Window::makeActive()
    {
        glfwMakeContextCurrent( this->window );
    }
    void Window::swapBuffers()
    {
        glfwSwapBuffers( this->window );
    }
    /** Iconifies/minimizes window
        \sa restore(), glfwIconifyWindow()
    */
    void Window::iconify ()
    {
        glfwIconifyWindow( this->window );
    }
    /** restores current window
        \sa iconify(), glfwRestoreWindow()
    */
    void Window::restore ()
    {
        glfwRestoreWindow( this->window );
    }
    /** makes window visible if it was hidden
        \sa hide(), glfwShowWindow()
    */
    void Window::show ()
    {
        glfwShowWindow( this->window );
    }
    /** hides window if it was visable
        \sa show(), glfwHideWindow()
    */
    void Window::hide()
    {
        glfwHideWindow( this->window );
    }

    /** Set window's "should close" flag
        \param[in] - GL_TRUE if window should close
                   - GL_FALSE if window should stay open
        \param[out] returns value of flag (GL_TRUE or GL_FALSE)
    */
    int Window::shouldClose( int gl_tf )
    {
        glfwSetWindowShouldClose( this->window, gl_tf );
        return gl_tf;
    }

} // namespace sre

//
//#include "window.hpp"
//#include <iostream>
//
//namespace sre
//{
//    /////////////
//    //VideoMode//
//
//    VideoMode::VideoMode ( Monitor * monitor )
//        : VideoMode ( monitor->getVideoMode() )
//    {
//    }
//    VideoMode::VideoMode ( VideoMode * videoMode )
//    {
//            this->vidMode = videoMode->vidMode;
//    }
//    VideoMode::VideoMode ( const GLFWvidmode * vidmode)
//    {
//        *( this->vidMode ) = *vidmode;
//    }
//
//    void VideoMode::setWidth ( int width ) { vidMode->width = width; }
//    void VideoMode::setHeight ( int height ) { vidMode->height = height; }
//    void VideoMode::setRedBits ( int redBits ) { vidMode->redBits = redBits; }
//    void VideoMode::setGreenBits ( int greenBits ) { vidMode->greenBits  = greenBits; }
//    void VideoMode::setBlueBits ( int blueBits ) { vidMode->blueBits = blueBits; }
//    void VideoMode::setRefreshRate ( int refreshRate ) { vidMode->refreshRate = refreshRate; }
//
//    int VideoMode::getWidth () const { return vidMode->width; }
//    int VideoMode::getHeight () const { return vidMode->height; }
//    int VideoMode::getRedBits () const { return vidMode->redBits; }
//    int VideoMode::getGreenBits () const { return vidMode->greenBits; }
//    int VideoMode::getBlueBits () const { return vidMode->blueBits; }
//    int VideoMode::getRefreshRate () const { return vidMode->refreshRate; }
//
//    /////////////
//    //GammaRamp//
//
//
//    ///////////
//    //Monitor//
//
//    Monitor::Monitor ()
//    {
//        monitor = glfwGetPrimaryMonitor();
//    }
//    Monitor::Monitor (GLFWmonitor * monitor)
//    {
//        this->monitor = monitor;
//        glfwGetMonitorPos( this->monitor, &posXY[0], &posXY[1] );
//        glfwGetMonitorPhysicalSize( this->monitor, &physSize[0], &physSize[1] );
//        name = glfwGetMonitorName( this->monitor );
//    }
//    VideoMode Monitor::getVideoMode () const
//    {
//        return VideoMode( glfwGetVideoMode ( monitor ) );
//    }
//    int * Monitor::getPos ()
//    {
//        glfwGetMonitorPos( monitor, &posXY[0], &posXY[1] );
//        return posXY;
//    }
//    int * Monitor::getPhysicalSize ()
//    {
//        glfwGetMonitorPhysicalSize( monitor, &physSize[0], &physSize[1] );
//        return physSize;
//    }
//    GLFWmonitor * Monitor::getGLFWMonitor () const
//    {
//        return monitor;
//    }
//    Monitor Monitor::getPrimary ()
//    {
//        return Monitor( glfwGetPrimaryMonitor() );
//    }
//
//    //////////
//    //Window//
//    Window::Window ( GLFWwindow * window )
//    {
//        this->window = window;
//    }
//    Window::Window ( int width, int height, std::string title , Monitor monitor)
//    {
//        this->width = width;
//        this->height = height;
//        this->title = title;
//        this->monitor = monitor;
//        windowSettings = WindowSettings();
//        frameBufferSettings = FrameBufferSettings();
//        contextSettings = ContextSettings();
//        apply(); // apply all GLFW hints
//    }
//    //set
//    void Window::setWindowPos ( int xpos, int ypos )
//    {
//        glfwSetWindowPos( window, xpos, ypos );
//    }
//    void Window::setWindowPosX ( int xpos )
//    {
//        glfwSetWindowPos( window, xpos, this->y );
//    }
//    void Window::setWindowPosY ( int ypos )
//    {
//        glfwSetWindowPos( window, this->x, ypos );
//    }
//    void Window::setWindowSize ( int width, int height)
//    {
//        glfwSetWindowSize ( window, width, height );
//    }
//    void Window::setWindowWidth ( int width )
//    {
//        glfwSetWindowSize ( window, width, this->height );
//    }
//    void Window::setWindowHeight ( int height )
//    {
//        glfwSetWindowSize ( window, height, this->height );
//    }
//    void Window::setWindowShouldClose ( bool tf )
//    {
//        glfwSetWindowShouldClose ( window , tf );
//    }
//
//    //get
//    bool Window::isFocused () const
//    {
//        return glfwGetWindowAttrib( window, GLFW_FOCUSED );
//    }
//    bool Window::isIconified () const
//    {
//        return glfwGetWindowAttrib( window, GLFW_ICONIFIED );
//    }
//    bool Window::isResizable () const
//    {
//        return glfwGetWindowAttrib( window, GLFW_RESIZABLE );
//    }
//    bool Window::isDecorated () const
//    {
//        return glfwGetWindowAttrib( window, GLFW_DECORATED );
//    }
//    int Window::getWindowPosX ()
//    {
//        glfwGetWindowPos( window, &x, NULL );
//        return x;
//    }
//    int Window::getWindowPosY ()
//    {
//        glfwGetWindowPos( window, NULL, &y );
//        return y;
//    }
//
//    int Window::getWindowWidth ()
//    {
//        glfwGetWindowSize( window, &width, NULL );
//        return width;
//    }
//    int Window::getWindowHeight ()
//    {
//        glfwGetWindowSize( window, NULL, &height );
//    }
//    int Window::getFrameBufferSizeX ()
//    {
//        glfwGetFramebufferSize( window, &x, NULL );
//        return x;
//    }
//    int Window::getFrameBufferSizeY ()
//    {
//        glfwGetFramebufferSize( window, &y, NULL );
//    }
//
//    bool Window::windowShouldClose () const
//    {
//        glfwWindowShouldClose( window );
//    }
//
//    void Window::swapBuffers()
//    {
//        glfwSwapBuffers( window );
//    }
//
//    void Window::apply()
//    {
//        //all other settings
//        windowSettings.apply();
//        frameBufferSettings.apply();
//        contextSettings.apply();
//        window = glfwCreateWindow( width, height, title.c_str(), monitor.getGLFWMonitor(), NULL );
//    }
//    void Window::setActive()
//    {
//        glfwMakeContextCurrent( window );
//    }
//
//    Window Window::getActive()
//    {
//        return Window( glfwGetCurrentContext() );
//    }
//
//    // settings classes
//    void Settings::apply() const
//    {
//        // bool and GL_TRUE and GL_FALSE don't play nicely: LET ME KNOW!
//        if (! ( (int(true) == int(GL_TRUE)) && ( int(false) == int(GL_FALSE) ) ) )
//        {
//            std::cerr<< "ERROR: bool true, false != GL_TRUE, GL_FALSE!";
//        }
//    }
//
//    void WindowSettings::apply() const
//    {
//        Settings::apply();
//        glfwWindowHint( GLFW_RESIZABLE, isResizable() );
//        glfwWindowHint( GLFW_VISIBLE, isVisible() );
//        glfwWindowHint( GLFW_DECORATED, isDecorated() );
//    }
//
//    void FrameBufferSettings::apply() const
//    {
//        Settings::apply();
//        glfwWindowHint( GLFW_RED_BITS, getRedBits() );
//        glfwWindowHint( GLFW_GREEN_BITS, getGreenBits() );
//        glfwWindowHint( GLFW_BLUE_BITS, getBlueBits() );
//        glfwWindowHint( GLFW_ALPHA_BITS, getAlphaBits() );
//        glfwWindowHint( GLFW_DEPTH_BITS, getDepthBits() );
//        glfwWindowHint( GLFW_STENCIL_BITS, getStencilBits() );
//
//        glfwWindowHint( GLFW_ACCUM_RED_BITS, getAccumRedBits() );
//        glfwWindowHint( GLFW_ACCUM_GREEN_BITS, getAccumGreenBits() );
//        glfwWindowHint( GLFW_ACCUM_BLUE_BITS, getAccumBlueBits() );
//        glfwWindowHint( GLFW_ACCUM_ALPHA_BITS, getAccumAlphaBits() );
//        glfwWindowHint( GLFW_AUX_BUFFERS, getAuxBuffers() );
//        glfwWindowHint( GLFW_SAMPLES, getSamples() );
//        glfwWindowHint( GLFW_REFRESH_RATE, getRefreshRate() );
//
//        glfwWindowHint( GLFW_STEREO, isStereo() );
//        glfwWindowHint( GLFW_SRGB_CAPABLE, isSRGBCapable() );
//    }
//
//    void ContextSettings::apply() const
//    {
//        Settings::apply();
//        switch (api)
//        {
//        case GL:
//            glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_API );
//            break;
//        case GL_ES:
//            glfwWindowHint( GLFW_CLIENT_API, GLFW_OPENGL_ES_API );
//            break;
//        default:
//            break;
//            //enum has no value...
//        }
//
//        glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, getVersionMajor() );
//        glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, getVersionMinor() );
//
//        switch (robustness)
//        {
//        case NO_ROBUSTNESS:
//            glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_ROBUSTNESS );
//            break;
//        case NO_RESET_NOTIFICATION:
//            glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, GLFW_NO_RESET_NOTIFICATION );
//            break;
//        case LOSE_CONTEXT_ON_RESET:
//            glfwWindowHint( GLFW_CONTEXT_ROBUSTNESS, GLFW_LOSE_CONTEXT_ON_RESET );
//            break;
//        default:
//            break;
//            //enum has no value...
//        }
//
//        glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, isForwardCompatible() );
//        glfwWindowHint( GLFW_OPENGL_DEBUG_CONTEXT, isDebugContext() );
//
//        switch (profile)
//        {
//        case ANY_PROFILE:
//            glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE );
//            break;
//        case COMPAT_PROFILE:
//            glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE );
//            break;
//        case CORE_PROFILE:
//            glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
//            break;
//        default:
//            break;
//            //enum has no value...
//        }
//
//    }
//}
//
//
//
//
//
