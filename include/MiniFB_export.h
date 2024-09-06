#ifndef _MINIFB_EXPORT_H_
#define _MINIFB_EXPORT_H_

#if defined(_WIN32)
    #define MFB_EXPORT __declspec(dllexport)
#else
    #define MFB_EXPORT 
#endif

#endif