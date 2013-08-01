#include <GLFW/glfw3.h>

#include "monitor.hpp"

//== namespace ==//
namespace sre {

//== VideoMode class ==//
/** \class VideoMode
    A class representing the video mode of a particular monitor
  * \sa Monitor, GLFWvidmode*/
    //// ctor ////
/** Constructs a VideoMode from the primary monitor */
VideoMode::VideoMode() {
    this->vidmode = glfwGetVideoMode ( glfwGetPrimaryMonitor() );
}
/** Constructs a VideoMode containing a GLFWvidmode
  * \param[in] vidmode the pointer to the GLFWvidmode to be associated with this object*/
VideoMode::VideoMode ( const GLFWvidmode * vidmode ) {
    this->vidmode= vidmode;
}
    //// get methods ////
/** \return width, in screen coordinates, of the video mode \sa GLFWvidmode::width*/
int VideoMode::width ()        { return vidmode->width; }
/** \return height, in screen coordinates, of the video mode \sa GLFWvidmode::height*/
int VideoMode::height ()       { return vidmode->height; }
/** \return bit depth of the red channel of the video mode \sa GLFWvidmode::redBits*/
int VideoMode::redBits ()      { return vidmode->redBits; }
/** \return bit depth of the green channel of the video mode \sa GLFWvidmode::greenBits*/
int VideoMode::greenBits ()    { return vidmode->greenBits; }
/** \return bit depth of the blue channel of the video mode \sa GLFWvidmode::blueBits*/
int VideoMode::blueBits ()     { return vidmode->blueBits; }
/** \return refresh rate, in Hz, of the video mode \sa GLFWvidmode::refreshRate*/
int VideoMode::refreshRate ()  { return vidmode->refreshRate; }




//== GammaRamp class ==//
GammaRamp::GammaRamp ( const GLFWgammaramp * gammaRamp ) {
    this->gammaRamp = gammaRamp;
}
const GLFWgammaramp * GammaRamp::getGLFWgammaramp () {
    return this->gammaRamp;
}

//== Monitor class ==//
Monitor::Monitor ( GLFWmonitor * monitor ) {
    this->monitor = monitor;
}
GLFWmonitor * Monitor::Monitor::getGLFWMonitor() const {
    return this->monitor;
}
Monitor Monitor::getPrimaryMonitor () {
    return Monitor ( glfwGetPrimaryMonitor() );
}
void Monitor::setGammaRamp ( GammaRamp gammaRamp ) {
    glfwSetGammaRamp(this->monitor, gammaRamp.getGLFWgammaramp() );
}
void Monitor::setGamma ( float gamma ) {
    glfwSetGamma(this->monitor, gamma);
}
    //// get methods ////
VideoMode getVideoMode () {
    }

} //namespace sre
