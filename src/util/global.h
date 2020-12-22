#ifndef GLOBAL_H_06112020
#define GLOBAL_H_06112020

#ifdef CE_PLAT_WIN32
    #ifdef CE_BUILDING_LIB
        #ifdef __GNUC__
            #define EXPORT __attribute__ ((dllexport))
        #else
            #define EXPORT __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define EXPORT __attribute__ ((dllimport))
        #else
            #define EXPORT __declspec(dllimport)
        #endif
    #endif
    #define LOCAL
#else
    #if __GNUC__ >= 4
        #define EXPORT __attribute__ ((visibility ("default")))
        #define LOCAL  __attribute__ ((visibility ("hidden")))
    #else
        #define EXPORT
        #define LOCAL
    #endif
#endif

#endif