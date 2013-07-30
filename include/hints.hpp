#ifndef HINTS_HPP
#define HINTS_HPP

#include <GLFW/glfw3.h>
#include <map>
#include <iostream>

namespace sre
{
    /** Represents a set of GLFW Hints **/
    class Hints
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
        /** Applies GLFW/OpenGL settings for window, its context, and framebuffers **/
        virtual void apply() const =0;
    };

    class MapHints : public Hints, public std::map<Hints::KEY, int>
    {
        static void applyHint (const Hints::KEY & key, const int & val );

        protected:
        struct Hint : public std::pair< Hints::KEY , int>
        {
        public:
            Hint( Hints::KEY key, int val) : std::pair<Hints::KEY, int>( key, val ) {}
        };

        public:
        void apply() const;
    };

    class DefaultHints : public Hints
    {
        public:
        void apply() const;
    };

    class WindowHints : public MapHints
    {
        bool _resizable = true;
        bool _visible = true;
        bool _decorated = true;
    public:
        WindowHints();

        //void apply() const;

        void resizable ( bool tf )  { (*this)[RESIZABLE] = tf; }
        void visible ( bool tf )    { (*this)[VISIBLE] = tf; }
        void decorated ( bool tf )  { (*this)[DECORATED] = tf; }
    };

    class FramebufferHints: public Hints
    {
        int _redBits = 8;
        int _greenBits = 8;
        int _blueBits = 8;
        int _alphaBits = 8;
        int _depthBits = 24;
        int _stencilBits = 8;
        int _accumRedBits = 0;
        int _accumGreenBits = 0;
        int _accumBlueBits = 0;
        int _accumAlphaBits = 0;
        int _auxBuffers = 0;
        int _samples = 0;
        int _refreshRate = 0;
        bool _stereo = false;
        bool _sRGBCapable = false;
    public:
        void apply() const;

        void redBits ( int bits ) { _redBits = bits; }
        void greenBits ( int bits ) { _greenBits = bits; }
        void blueBits ( int bits ) { _blueBits = bits; }
        void alphaBits ( int bits ) { _alphaBits = bits; }
        void depthBits ( int bits ) { _depthBits = bits; }
        void stencilBits ( int bits ) { _stencilBits = bits; }
        void accumRedBits ( int bits ) { _accumRedBits = bits; }
        void accumGreenBits ( int bits ) { _accumGreenBits = bits; }
        void accumBlueBits ( int bits ) { _accumBlueBits = bits; }
        void accumAlphaBits ( int bits ) { _auxBuffers = bits; }
        void auxBuffers ( int buffers ) { _auxBuffers = buffers; }
        void samples ( int samples ) { _samples = samples; }
        void refreshRate ( int frameHz ) { _refreshRate = frameHz; }
        void stereo ( bool tf ) { _stereo = tf; }
        void sRBGCapable ( bool tf ) { _sRGBCapable = tf; }

    };

    class ContextHints : Hints
    {
        enum API
        {
            OPENGL_API,
            OPENGL_ES_API,
        } _api;

        int _versionMajor;
        int _versionMinor;

        enum Robustness
        {
            NO_ROBUSTNESS,
            NO_RESET_NOTIFICATION,
            LOSE_CONTEXT_ON_RESET,
        } _robustness;

        bool _forwardCompat;
        bool _debugContext;

        enum Profile
        {
            ANY,
            OPENGL_COMPAT,
            OPENGL_CORE,
        } _profile;

    public:
        void setAPIES ( bool tf ) { _api = (tf) ? OPENGL_ES_API : OPENGL_API; }
        void versionMajor ( int versionNum ) { _versionMajor = versionNum; }
        void versionMinor ( int versionNum ) { _versionMinor = versionNum; }
        void setNoRobustness () { _robustness = NO_ROBUSTNESS; }
        void setNoResetNotification ( ) { _robustness = NO_RESET_NOTIFICATION; }
        void setLoseContextOnReset ( ) { _robustness = LOSE_CONTEXT_ON_RESET; }
        void forwardCompat ( bool tf ) { _forwardCompat = tf; }
        void debug ( bool tf ) { _debugContext = tf; }
    };

} // namespace sre

#endif // HINTS_HPP
