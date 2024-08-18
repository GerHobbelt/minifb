#include <MiniFB_version.h>

const mfb_build_version_t mfb_build_version = { MFB_VERSION_MAJOR, MFB_VERSION_MINOR, MFB_VERSION_PATCH, 0 };

const char mfb_build_variant[] =
#if defined(__ANDROID__)
    "android"
#elif defined(WIN_TARGET)
    "windows"
#elif defined(IOS_TARGET)
    "ios"
#elif defined(MACOS_TARGET)
    "macos"
#elif defined(UNIX_TARGET)
    "unix"
#elif defined(EMSCRIPTEN_TARGET)
    "emscripten"
#else
    "unknown"
#endif
#if defined(USE_OPENGL_API)
    "-opengl"
#endif
#if defined(USE_METAL_API)
    "-metal"
#endif
#if defined(USE_WAYLAND_API)
    "-wayland"
#endif
#if defined(USE_INVERTED_Y_ON_MACOS)
    "-invertedy"
#endif
#if defined(DEBUG)
    "-debug"
#endif
    ;