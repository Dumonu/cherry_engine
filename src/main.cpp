#include <stdio.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

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

        engine.Start();

        return 0;
    }
    catch(CherryEngine::Exception e)
    {
        fprintf(stderr, "Uncaught Exception:\n\t%s\n", e.what());
        return 1;
    }
}