#ifndef _MINIFB_EXPORT_H_
#define _MINIFB_EXPORT_H_

#if defined(WIN32) || defined(WIN_TARGET)
    #define MFB_EXPORT __declspec(dllexport)
#else
    #define MFB_EXPORT 
#endif

#endif