#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "global.h"
#include "CherryEngine.h"
#include "settings.h"
#include "Exception.h"

int main(int argc, char** argv)
{
    try
    {
        CherryEngine::Engine engine;

        for(int i = 0; i < CherryEngine::S_NUM; ++i){
            printf("%s: %d\n", CherryEngine::SettingNameStr[i],
                CherryEngine::DefaultSettingValue[i]);
        }

        sleep(10);

        return 0;
    }
    catch(CherryEngine::Exception e)
    {
        fprintf(stderr, "Uncaught Exception:\n\t%s\n", e.what());
        return 1;
    }
}