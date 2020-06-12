#ifndef GLOBAL_H_06112020
#define GLOBAL_H_06112020

// This header is meant to convert unistd.h calls to Windows.h calls when relevant.

#ifdef _WIN32
#include <Windows.h>
#define sleep(x) Sleep((x) * 1000)
#else
#include <unistd.h>
#endif

#endif