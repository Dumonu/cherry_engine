#include <stdio.h>
#include <limits.h>

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "CherryEngine.h"
#include "settings.h"
#include "Exception.h"

#include "Shader.h"

int main(void)
{
    try
    {
        CherryEngine::Engine engine;

        for(int i = 0; i < CherryEngine::S_NUM; ++i){
            printf("%s: %d\n", CherryEngine::SettingNameStr[i],
                CherryEngine::DefaultSettingValue[i]);
        }

        CherryEngine::Shader shader(2,
            GL_VERTEX_SHADER, "E:/Other_Stuff/logistic_visualizer/src/logcurve.vert",
            GL_FRAGMENT_SHADER, "E:/Other_Stuff/logistic_visualizer/src/logcurve.frag"
        );

        engine.Start();

        return 0;
    }
    catch(CherryEngine::Exception e)
    {
        fprintf(stderr, "Uncaught Exception:\n\t%s\n", e.what());
        return 1;
    }
}