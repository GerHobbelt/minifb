#ifndef _MINIFB_VERSION_H_
#define _MINIFB_VERSION_H_

#include "MiniFB_export.h"

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

MFB_EXPORT extern const mfb_build_version_t mfb_build_version;
MFB_EXPORT extern const char                mfb_build_variant[];

#endif