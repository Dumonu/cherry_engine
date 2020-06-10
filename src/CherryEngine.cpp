#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "version.h"
#include "log.h"
#include "Exception.h"
#include "CherryEngine.h"
#include "settings.h"

namespace CherryEngine {

Engine::Engine() : Engine(NULL) {}

Engine::Engine(const char* settingsfile)
{
    // VERSION CHECKS
    LogDebug("CherryEngine::Engine::Engine - CherryEngine version %i.%i.%i.%x\n",
        VERSION_MAJOR,
        VERSION_MINOR,
        VERSION_REVISION,
        VERSION_TWEAK
    );

    LogDebug("CherryEngine::Engine::Engine - Compiled against GLFW %i.%i.%i\n",
        GLFW_VERSION_MAJOR,
        GLFW_VERSION_MINOR,
        GLFW_VERSION_REVISION
    );

    int glfw_major, glfw_minor, glfw_revision;
    glfwGetVersion(&glfw_major, &glfw_minor, &glfw_revision);
    LogDebug("CherryEngine::Engine::Engine - Running against GLFW %i.%i.%i\n",
        glfw_major,
        glfw_minor,
        glfw_revision
    );

    // LIBRARY INITIALIZATION
    if(!glfwInit())
    {
        const char *err;
        int ret = glfwGetError(&err);
        throw Exception("Error initializing GLFW (%d): %s\n", ret, err);
    }
    LogDebug("CherryEngine::Engine::Engine - GLFW Initialized\n");

    if(settingsfile == NULL) // No file given: Default settings
    {
        for(int i = 0; i < S_NUM + 1; ++i)
        {
            m_settings[i] = DefaultSettingValue[i];
        }
        LogDebug("CherryEngine::Engine::Engine - Default Settings Loaded\n");
    }
    else
    {
        throw Exception("Error initializing CherryEngine: Loading from file not yet implemented\n");
    }

    // Create window and context
}

Engine::~Engine()
{
    glfwTerminate(); // safe even when GLFW not initialized
    LogDebug("CherryEngine::Engine::~Engine - GLFW Terminated\n");
}

}