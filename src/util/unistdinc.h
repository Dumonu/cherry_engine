#ifndef UNISTDINC_H_12212020
#define UNISTDINC_H_12212020

// convert unistd.h calls to Windows.h calls
#ifdef CE_PLAT_WIN32
    #include <Windows.h>
    #define sleep(x) Sleep((x) * 1000)
#else
    #include <unistd.h>
#endif

#endif