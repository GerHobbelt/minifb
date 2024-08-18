#ifndef _MINIFB_VERSION_H_
#define _MINIFB_VERSION_H_

// macro definition checks taken from here: https://stackoverflow.com/a/48685077

#if !defined(MFB_VERSION_MAJOR) || (~(~MFB_VERSION_MAJOR + 0) == 0 && ~(~MFB_VERSION_MAJOR + 1) == 1)
    #undef MFB_VERSION_MAJOR
    #define MFB_VERSION_MAJOR (0)
#endif

#if !defined(MFB_VERSION_MINOR) || (~(~MFB_VERSION_MINOR + 0) == 0 && ~(~MFB_VERSION_MINOR + 1) == 1)
    #undef MFB_VERSION_MINOR
    #define MFB_VERSION_MINOR (0)
#endif

#if !defined(MFB_VERSION_PATCH) || (~(~MFB_VERSION_PATCH + 0) == 0 && ~(~MFB_VERSION_PATCH + 1) == 1)
    #undef MFB_VERSION_PATCH
    #define MFB_VERSION_PATCH (0)
#endif

typedef struct {
    unsigned char major, minor, patch, _reserved;
} mfb_build_version_t;

extern mfb_build_version_t const mfb_build_version;

extern const char* const mfb_build_variant;

#endif