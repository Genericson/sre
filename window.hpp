#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <GLFW/glfw3.h>
#include <string>
#include "include/hints.hpp"
#include <glm/glm.hpp>

namespace sre
{
    using namespace glm;
    // !! temp !!
    class Monitor
    {
        GLFWmonitor * monitor;
    public:
        Monitor ( GLFWmonitor * monitor ) { this->monitor = monitor; }
        GLFWmonitor * getGLFWMonitor() { return this->monitor; }

        static Monitor getPrimaryMonitor ()
        {
            return Monitor( glfwGetPrimaryMonitor() );
        }
    };


    class Window
    {
        GLFWwindow * window;
    public:
        Window ( GLFWwindow * window );
        Window ( int width=640, int height=480,
               std::string title="OpenGL",
               Monitor monitor = Monitor( nullptr ),
               Window share = Window( nullptr ) );
        // get
        GLFWwindow * getGLFWwindow() { return this->window; }
        ivec2 getFramebufferSize()
        {
            ivec2 size;
            glfwGetFramebufferSize( this->window, &size.x, &size.y );
            return size;
        }
        // bool get
        std::string getTitle () const;
        ivec2 getPos () const;
        ivec2 getSize () const;

        bool exists () const;
        bool shouldClose () const;

        // set
        void setTitle( std::string title);
        void setPos ( int xPos, int yPos );
        void setPos ( ivec2 pos);
        void setSize ( int xSize, int ySize );
        void setSize ( ivec2 size );

        // set command
        void makeActive ();
        void iconify ();
        void restore ();
        void show ();
        void hide ();
        bool shouldClose ( bool tf );
        void swapBuffers ();

        // callbacks

    };
}

#endif // WINDOW_HPP


//#ifndef WINDOW_HPP_INCLUDED
//#define WINDOW_HPP_INCLUDED
//
//
//#include <GLFW/glfw3.h>
//
//#include <string>
//
//
//namespace sre //Stupit? Rendering Engine
//{
//    class VideoMode;
//    class GammaRamp;
//    class Monitor;
//    class Window;
//    class WindowSettings;
//    class FrameBufferSettings;
//    class ContextSettings;
//
//    class VideoMode
//    {
//        GLFWvidmode * vidMode;
//
//    public:
//        VideoMode ( Monitor * monitor );
//        VideoMode ( VideoMode * videoMode );
//        VideoMode ( const GLFWvidmode * vidmode);
//
//        void setWidth ( int width );
//        void setHeight ( int height );
//        void setRedBits ( int redBits );
//        void setGreenBits ( int greenBits );
//        void setBlueBits ( int blueBits );
//        void setRefreshRate ( int refreshRate );
//
//        int getWidth () const;
//        int getHeight () const;
//        int getRedBits () const;
//        int getGreenBits () const;
//        int getBlueBits () const;
//        int getRefreshRate () const;
//    };
//
//    class GammaRamp
//    {
//
//    };
//
//    /** \brief
//     *
//     *
//     */
//    class Monitor
//    {
//        GLFWmonitor * monitor;
//        int posXY[2];
//        int physSize[2];
//        std::string name;
//
//
//
//    public:
//        Monitor ();
//        Monitor ( GLFWmonitor * monitor);
//
//        // get
//        int * getPos ();
//        int * getPhysicalSize ();
//        VideoMode getVideoMode () const;
//        GammaRamp getGammaRamp () const;
//        GLFWmonitor * getGLFWMonitor () const;
//
//        // static
//        static Monitor getPrimary();
//    };
//
//    class Settings
//    {
//        public:
//        void apply() const;
//    };
//
//    class WindowSettings : private Settings
//    { // http://www.glfw.org/docs/3.0/window.html for default values
//        bool resizable = true;
//        bool visible = true;
//        bool decorated = true;
//    public:
//        WindowSettings () {}
//        WindowSettings ( bool resizable, bool visible, bool decorated )
//        {
//            setResizable( resizable );
//            setVisible ( visible );
//            setDecorated ( decorated );
//        }
//
//        void setResizable( bool resizable ) { this->resizable = resizable; }
//        void setVisible ( bool visible ) { this->visible = visible; }
//        void setDecorated ( bool tf ) { this->decorated = decorated; }
//
//        bool isResizable() const { return resizable; }
//        bool isVisible() const { return visible; }
//        bool isDecorated() const { return decorated; }
//
//        //other
//        void apply() const;
//    };
//
//    class FrameBufferSettings : private Settings
//    { // http://www.glfw.org/docs/3.0/window.html for default values
//        int redBits = 8, greenBits = 8, blueBits = 8;
//        int alphaBits = 8;
//        int depthBits = 24;
//        int stencilBits = 8;
//
//        int accumRedBits = 0, accumGreenBits = 0, accumBlueBits = 0;
//        int accumAlphaBits = 0;
//        int auxBuffers = 0;
//        int samples = 0;
//        int refreshRate = 0;
//
//        bool stereo = false;
//        bool sRGBCapable = false;
//
//    public:
//        FrameBufferSettings () {}
//
//        int getRedBits () const { return redBits; }
//        int getGreenBits() const { return greenBits; }
//        int getBlueBits () const { return blueBits; }
//        int getAlphaBits () const { return alphaBits; }
//        int getDepthBits () const { return depthBits; }
//        int getStencilBits () const { return stencilBits; }
//
//        int getAccumRedBits () const { return accumRedBits; }
//        int getAccumGreenBits () const { return accumGreenBits; }
//        int getAccumBlueBits () const { return accumBlueBits; }
//        int getAccumAlphaBits () const { return accumAlphaBits; }
//
//        int getAuxBuffers () const { return auxBuffers; }
//        int getSamples () const { return samples; }
//        int getRefreshRate () const { return refreshRate; }
//
//        bool isStereo () const { return stereo; }
//        bool isSRGBCapable () const { return sRGBCapable; }
//
//        void setRedBits ( int redBits ) { this->redBits = redBits; }
//        void setGreenBits ( int greenBits ) { this->greenBits = greenBits; }
//        void setBlueBits ( int blueBits ) { this->blueBits = blueBits; }
//        void setAlphaBits ( int alphaBits ) { this->alphaBits = alphaBits; }
//        void setDepthBits ( int depthBits ) { this->depthBits = depthBits; }
//        void setStencilBits ( int stencilBits ) { this->stencilBits = stencilBits; }
//
//        void setAccumRedBits ( int accumRedBits ) { this->accumRedBits = accumRedBits; }
//        void setAccumGreenBits ( int accumGreenBits ) { this->accumGreenBits = accumGreenBits; }
//        void setAccumBlueBits ( int accumBlueBits ) { this->accumBlueBits = accumBlueBits; }
//        void setAccumAlphaBits ( int alphaBits ) { this->alphaBits = alphaBits; }
//
//        void setAuxBuffers ( int auxBuffers ) { this->auxBuffers = auxBuffers; }
//        void setSamples ( int samples ) { this->samples = samples; }
//        void setRefreshRate ( int refreshRate ) { this->refreshRate = refreshRate; }
//
//        void setStereo ( bool stereo ) { this->stereo = stereo; }
//        void setSRGBCapable ( bool sRGBCapable ) { this->sRGBCapable = sRGBCapable; }
//
//        //other
//        void apply() const;
//    };
//
//    class ContextSettings : private Settings
//    { // http://www.glfw.org/docs/3.0/window.html for default values
//        enum API
//        {
//            GL,
//            GL_ES
//        };
//        API api = GL;
//
//        int versionMajor = 1;
//        int versionMinor = 0;
//
//        enum ROBUSTNESS
//        {
//            NO_ROBUSTNESS,
//            NO_RESET_NOTIFICATION,
//            LOSE_CONTEXT_ON_RESET
//        };
//        ROBUSTNESS robustness = NO_ROBUSTNESS;
//
//        bool forwardCompat = false;
//        bool debugContext = false;
//
//        enum PROFILE
//        {
//            ANY_PROFILE,
//            COMPAT_PROFILE,
//            CORE_PROFILE
//        };
//        PROFILE profile = ANY_PROFILE;
//
//    public:
//        ContextSettings () {}
//
//        // set
//        void setAPIGL () { api = GL; }
//        void setAPIGLES () { api = GL_ES; }
//
//        void setVersionMajor ( int versionMajor ) { this->versionMajor = versionMajor; }
//        void setVersionMinor ( int versionMinor ) { this->versionMinor = versionMinor; }
//
//        void setNoRobustness () { robustness = NO_ROBUSTNESS; }
//        void setNoResetNotification () { robustness = NO_RESET_NOTIFICATION; }
//        void setLoseContextOnReset () { robustness = LOSE_CONTEXT_ON_RESET; }
//
//        void setForwardCompat ( bool forwardCompatible ) { this->forwardCompat = forwardCompatible;  }
//        void setDebugContext ( bool debugContext ) { this->debugContext = debugContext; }
//
//        void setProfileAny () { this->profile = ANY_PROFILE; }
//        void setProfileCompat () { this->profile = COMPAT_PROFILE; }
//        void setProfileCore () { this->profile = CORE_PROFILE; }
//
//        // get
//        bool isAPIGL () const { return (this->api == GL); }
//        bool isAPIGLES () const { return (this->api == GL_ES); }
//
//        int getVersionMajor () const { return this->versionMajor; }
//        int getVersionMinor () const { return this->versionMinor; }
//
//        bool isNoRobustness () const { return (this->robustness == NO_ROBUSTNESS); }
//        bool isNoResetNotification () const { return (this->robustness == NO_RESET_NOTIFICATION); }
//        bool isLoseContextOnReset () const { return( this->robustness == LOSE_CONTEXT_ON_RESET); }
//
//        bool isForwardCompatible () const { return forwardCompat;  }
//        bool isDebugContext () const { return debugContext; }
//
//        bool isProfileAny () const { return (this->profile == ANY_PROFILE); }
//        bool isProfileCompat () const { return (this->profile == COMPAT_PROFILE); }
//        bool isProfileCore () const { return (this->profile == CORE_PROFILE); }
//
//        //other
//        void apply() const;
//    };
//
//    /** \brief Abstraction of GLFW window structure and functions
//     *
//     *
//     */
//    class Window
//    {
//        GLFWwindow * window;
//
//        int width, height;
//        int x, y;
//        std::string title;
//        Monitor monitor;
//        WindowSettings windowSettings;
//        FrameBufferSettings frameBufferSettings;
//        ContextSettings contextSettings;
//
//        // apply settings to window's context
//        void apply ();
//        void applyWindowSettings () const;
//        void applyFrameBufferSettings () const;
//        void applyContextSettings() const;
//
//        Window (GLFWwindow * window);
//    public:
//        Window (int width=640, int height=480, std::string title="OpenGL" , Monitor monitor=Monitor::getPrimary() );
//        // set
//        void setWindowPos ( int xpos, int ypos );
//        void setWindowPosX ( int xpos );
//        void setWindowPosY ( int ypos );
//        void setWindowSize ( int width, int height);
//        void setWindowWidth ( int width );
//        void setWindowHeight ( int height );
//
//        void setWindowShouldClose ( bool tf );
//
//        //get
//        bool isFocused () const;
//        bool isIconified () const;
//        bool isResizable () const;
//        bool isDecorated () const;
//
//        //int getWindowPos ();
//        int getWindowPosX ();
//        int getWindowPosY ();
//        //int getWindowSize ();
//        int getWindowWidth ();
//        int getWindowHeight ();
//
//        int getFrameBufferSizeX ();
//        int getFrameBufferSizeY ();
//
//        bool windowShouldClose () const;
//
//        // other
//        void swapBuffers();
//        void setActive(); //makes the Window's context the current context
//
//        // static
//        Window getActive(); //returns active Window
//    };
//}
//
//#endif // WINDOW_HPP_INCLUDED
