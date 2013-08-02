#ifndef SRE_MONITOR_HPP
#define SRE_MONITOR_HPP

//== includes ==//
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
    VideoMode ( const GLFWvidmode& vidmode);

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
    // ctor
    Monitor ( GLFWmonitor * monitor );

    // get methods
    VideoMode getVideoMode ();
    std::list<VideoMode> getVideoModes ();
    GLFWmonitor * getGLFWMonitor() const;

    // set methods
    void setGammaRamp ( GammaRamp gammaRamp );
    void setGamma ( float gamma );

    // static methods
    static Monitor getPrimaryMonitor ();

}; //Monitor

} //namespace sre

#endif // SRE_MONITOR_HPP
