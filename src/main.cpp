#include <stdio.h>

#include "version.h"

int main(int argc, char** argv)
{
    printf("CherryEngine version %d.%d.%d.%x\n", VERSION_MAJOR, VERSION_MINOR, 
        VERSION_REVISION, VERSION_TWEAK);

    for(int i = 0; i < argc; ++i)
    {
        printf("%s%s", argv[i], i == argc - 1 ? "\n" : " ");
    }
    return 0;
}