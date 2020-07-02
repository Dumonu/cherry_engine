#include <cstdio>
#include <cstdarg>

#include "log.h"

namespace CherryEngine {

void LogDebug(const char* fmt, ...) noexcept
{
    std::va_list args;
    va_start(args, fmt);

    // TODO: Add checks for whether we should be logging for debug etc.
    vprintf(fmt, args);
    fflush(stdout);

    va_end(args);
}

}