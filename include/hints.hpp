#ifndef SRE_HINTS_HPP
#define SRE_HINTS_HPP

#include <GLFW/glfw3.h>
#include <map>
#include <iostream>

namespace sre
{
    class WindowAttribs
    {
    protected:
         // special values
        enum API
        {
            OPENGL_API,
            OPENGL_ES_API,
        };
        enum Robustness
        {
            NO_ROBUSTNESS,
            NO_RESET_NOTIFICATION,
            LOSE_CONTEXT_ON_RESET,
        };
        enum Profile
        {
            ANY,
            OPENGL_COMPAT,
            OPENGL_CORE,
        };

    public:
        enum KEY
        {
            RESIZABLE,
            VISIBLE,
            DECORATED,
            RED_BITS,
            GREEN_BITS,
            BLUE_BITS,
            ALPHA_BITS,
            DEPTH_BITS,
            STENCIL_BITS,
            ACCUM_RED_BITS,
            ACCUM_GREEN_BITS,
            ACCUM_BLUE_BITS,
            ACCUM_ALPHA_BITS,
            AUX_BUFFERS,
            SAMPLES,
            REFRESH_RATE,
            STEREO,
            SRGB_CAPABLE,
            CLIENT_API,
            VERSION_MAJOR,
            VERSION_MINOR,
            CONTEXT_ROBUSTNESS,
            OPENGL_FORWARD_COMPAT,
            OPENGL_DEBUG,
            OPENGL_PROFILE,
        };
        //// static methods ////
        static void getGLFWattrib ( const WindowAttribs::KEY & attrib,
                                    const int& val,
                                    int & attribGLFW,
                                    int & valGLFW );
    };
    class Hints : public WindowAttribs
    {
    public:
        virtual void apply() const =0;
    };

    class HintsMap : public Hints, public std::map<Hints::KEY, int>
    {
        static void applyHint (const Hints::KEY & key, const int & val );

        public:
        void apply() const;
    };

    class DefaultHints : public Hints
    {
        public:
        void apply() const;
    };

    class WindowHints : public HintsMap
    {

    public:
        WindowHints();
        void resizable  ( bool tf )  { (*this)[RESIZABLE] = tf; }
        void visible    ( bool tf )  { (*this)[VISIBLE] = tf; }
        void decorated  ( bool tf )  { (*this)[DECORATED] = tf; }
    };

    class FramebufferHints: public HintsMap
    {
    public:
        FramebufferHints();
        void redBits        ( int bits )    { (*this)[RED_BITS] = bits; }
        void greenBits      ( int bits )    { (*this)[GREEN_BITS] = bits; }
        void blueBits       ( int bits )    { (*this)[BLUE_BITS] = bits; }
        void alphaBits      ( int bits )    { (*this)[ALPHA_BITS] = bits; }
        void depthBits      ( int bits )    { (*this)[DEPTH_BITS] = bits; }
        void stencilBits    ( int bits )    { (*this)[STENCIL_BITS] = bits; }
        void accumRedBits   ( int bits )    { (*this)[ACCUM_RED_BITS] = bits; }
        void accumGreenBits ( int bits )    { (*this)[ACCUM_GREEN_BITS] = bits; }
        void accumBlueBits  ( int bits )    { (*this)[ACCUM_BLUE_BITS] = bits; }
        void accumAlphaBits ( int bits )    { (*this)[ACCUM_ALPHA_BITS] = bits; }
        void auxBuffers     ( int buffers ) { (*this)[AUX_BUFFERS] = buffers; }
        void samples        ( int samples ) { (*this)[SAMPLES] = samples; }
        void refreshRate    ( int frameHz ) { (*this)[REFRESH_RATE] = frameHz; }
        void stereo         ( bool tf )     { (*this)[STEREO] = tf; }
        void sRGBCapable    ( bool tf )     { (*this)[SRGB_CAPABLE] = tf; }
    };

    class ContextHints : public HintsMap
    {
    public:
        ContextHints();

        void setAPIES               ()          { (*this)[CLIENT_API] = OPENGL_ES_API; }
        void setAPIGL               ()          { (*this)[CLIENT_API] = OPENGL_API; }
        void versionMajor   ( int versionNum )  { (*this)[VERSION_MAJOR] = versionNum; }
        void versionMinor   ( int versionNum )  { (*this)[VERSION_MINOR] = versionNum; }
        void setNoRobustness        ()          { (*this)[CONTEXT_ROBUSTNESS] = NO_ROBUSTNESS; }
        void setNoResetNotification ()          { (*this)[CONTEXT_ROBUSTNESS] = NO_RESET_NOTIFICATION; }
        void setLoseContextOnReset  ()          { (*this)[CONTEXT_ROBUSTNESS] = LOSE_CONTEXT_ON_RESET; }
        void forwardCompat      ( bool tf )     { (*this)[OPENGL_FORWARD_COMPAT] = tf; }
        void debug              ( bool tf )     { (*this)[OPENGL_DEBUG] = tf; }
        void setProfileAny          ()          { (*this)[OPENGL_PROFILE] = ANY; }
        void setProfileCompat       ()          { (*this)[OPENGL_PROFILE] = OPENGL_COMPAT; }
        void setProfileCore         ()          { (*this)[OPENGL_PROFILE] = OPENGL_CORE; }
    };

} // namespace sre

#endif // HINTS_HPP
