#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "version.h"
#include "log.h"
#include "Exception.h"
#include "CherryEngine.h"
#include "settings.h"

namespace CherryEngine {

int Engine::instances = 0;

Engine::Engine() : Engine(NULL) {}

Engine::Engine(const char* settingsfile)
{
    if(instances++ == 0)
    {
        // only initialize globals on first creation
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
    }

    // Load default settings first, then replace with settings in file
    for (int i = 0; i < S_NUM + 1; ++i)
    {
        m_settings[i] = DefaultSettingValue[i];
    }
    LogDebug("CherryEngine::Engine::Engine - Default Settings Loaded\n");
    if(settingsfile != NULL) 
    {
        throw Exception("Error initializing CherryEngine: Loading from file not yet implemented\n");
    }

    // Create window and context
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
    glfwWindowHint(GLFW_CONTEXT_CREATION_API, GLFW_NATIVE_CONTEXT_API); // bad on wayland?
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, m_settings[S_AASamples]);

    m_window = glfwCreateWindow(
        m_settings[S_WinWidth],     // Width
        m_settings[S_WinHeight],    // Height
        VERSION_STR,                // Title
        m_settings[S_Fullscreen] ? glfwGetPrimaryMonitor() : NULL,  // Monitor - def = full
        NULL                        // Share context with other window
    );
    if(m_window == NULL)
    {
        const char *err;
        int ret = glfwGetError(&err);
        throw Exception("Error creating window (%d): %s\n", ret, err);
    }

    glfwSwapInterval(m_settings[S_VSync]);
}

Engine::~Engine()
{
    if(m_window != NULL)
    {
        glfwDestroyWindow(m_window);
        LogDebug("CherryEngine::Engine::~Engine - Window Destroyed\n");
    }
    if(--instances == 0)
    {
        glfwTerminate(); // safe even when GLFW not initialized
        LogDebug("CherryEngine::Engine::~Engine - GLFW Terminated\n");
    }
}

void Engine::Start()
{
    // Initialization
    while(!glfwWindowShouldClose(m_window))
    {
        // Update
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    //Finish
}

}