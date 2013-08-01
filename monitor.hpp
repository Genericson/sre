#ifndef SRE_MONITOR_HPP
#define SRE_MONITOR_HPP

//== includes ==//
#include <vector>
#include <list>

//== namespace ==//
namespace sre
{

//== forward declarations ==//

class VideoMode;
class GammaRamp;
class Monitor;

//== classes ==//
class VideoMode
{
    const GLFWvidmode * vidmode;

public:
    // ctor
    VideoMode ();
    VideoMode ( const GLFWvidmode * vidmode );

    // get methods
    int width ();
    int height ();
    int redBits ();
    int greenBits ();
    int blueBits ();
    int refreshRate ();

//    // static methods


}; //VideoMode

class GammaRamp
{
    const GLFWgammaramp * gammaRamp;

public:
    GammaRamp ( const GLFWgammaramp * gammaRamp );
    const GLFWgammaramp * getGLFWgammaramp ();
}; //GammaRamp

class Monitor
{
    GLFWmonitor * monitor;
public:
    Monitor ( GLFWmonitor * monitor );
    GLFWmonitor * getGLFWMonitor() const;
    static Monitor getPrimaryMonitor ();

    void setGammaRamp ( GammaRamp gammaRamp );
    void setGamma ( float gamma );

    VideoMode getVideoMode ();
    std::vector<VideoMode> getVideoModes ();
}; //Monitor

} //namespace sre

#endif // SRE_MONITOR_HPP
