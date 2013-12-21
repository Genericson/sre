#include <GLFW/glfw3.h>

#include "monitor.hpp"

//== namespace ==//
namespace sre {

//== VideoMode class ==//
/** \class VideoMode
 *  \brief A class representing the video mode of a particular monitor
 *  \sa Monitor, GLFWvidmode*/
    //// ctor ////
/** Constructs a VideoMode from the primary monitor */
VideoMode::VideoMode() {
    this->vidmode = glfwGetVideoMode ( glfwGetPrimaryMonitor() );
}
/** Constructs a VideoMode containing a GLFWvidmode
 *  \param[in] vidmode pointer to the GLFWvidmode to be associated with this object*/
VideoMode::VideoMode ( const GLFWvidmode * vidmode ) {
    this->vidmode = vidmode;
}
/** Constructs a VideoMode containing a GLFWvidmode
 *  \param[in] vidmode reference to the GLFWvidmode to be associated with this object*/
VideoMode::VideoMode ( const GLFWvidmode& vidmode ) {
    this->vidmode = &vidmode;
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
/** \class GammaRamp
 *  \brief A class representing the gamma ramp of a video mode
 *  \sa VideoMode, GLFWgammaramp */
    //// ctor ////
/** \param[in] gammaRamp gramma ramp to represent \sa GLFWgammaramp */
GammaRamp::GammaRamp ( const GLFWgammaramp * gammaRamp ) {
    this->gammaRamp = gammaRamp;
}
/** \return pointer to GLFWgammaramp contained in this object */
const GLFWgammaramp * GammaRamp::getGLFWgammaramp () {
    return this->gammaRamp;
}


//== Monitor class ==//
/** \class Monitor
 *  \brief A class representing a monitor
 *  \sa GLFWmonitor */
    //// ctor ////
/** Cunstruct Monitor from a pointer to a GLFWmonitor
 *  \param[in] monitor pointer to GLFWmonitor to represent */
Monitor::Monitor ( GLFWmonitor * monitor ) {
    this->monitor = monitor;
}
    //// get methods ////
/** \return current video mode of this monitor \sa glfwGetVideoMode*/
VideoMode Monitor::getVideoMode () {
    return VideoMode( glfwGetVideoMode(this->monitor) );
}
/** \return list of all video modes supported by this monitor \sa glfwGetVideoModes */
std::list<VideoMode> Monitor::getVideoModes () {
    int count;
    const GLFWvidmode * vidmodes = glfwGetVideoModes(this->monitor, &count);
    std::list<VideoMode> vidmodeList = std::list<VideoMode>();
    for( int i = 0; i < count; i++)
        vidmodeList.push_back( VideoMode(vidmodes[i]) );
    return vidmodeList;
}
/** \return pointer to GLFWmonitor contained in this Monitor \sa GLFWmonitor */
GLFWmonitor * Monitor::getGLFWMonitor() const {
    return this->monitor;
}
    //// set methods ////
/** Set the gamma ramp of this monitor
 *  \param[in] gammaRamp GammaRamp to use \sa glfwSetGamma*/
void Monitor::setGammaRamp ( GammaRamp gammaRamp ) {
    glfwSetGammaRamp(this->monitor, gammaRamp.getGLFWgammaramp() );
}
/** Set the gamma of the monitor
 *  \param[in] gamma gamma exponent to generate and apply a gamma ramp from
 *  \sa glfwSetGamma*/
void Monitor::setGamma ( float gamma ) {
    glfwSetGamma(this->monitor, gamma);
}
    //// static methods ////
/** \return primary monitor \sa glfwGetPrimaryMonitor */
Monitor Monitor::getPrimaryMonitor () {
    return Monitor( glfwGetPrimaryMonitor() );
}

} //namespace sre
