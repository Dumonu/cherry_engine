#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "version.h"
#include "log.h"
#include "Exception.h"
#include "CherryEngine.h"
#include "settings.h"

namespace CherryEngine {

int Engine::instances = 0;

void errCallbackGlfw(int err, const char* desc)
{
    LogDebug("GLFW Error (%d): %s\n", err, desc);
}

void errCallbackGl(GLenum src, GLenum type, GLuint id, GLenum sev, GLsizei len,
                   const GLchar *msg, const void *userparm)
{
    LogDebug("GL %s (type 0x%x, severity 0x%x, id %d): %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "Error" : "Message"), type, sev, id, msg);
}

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

        glfwSetErrorCallback(errCallbackGlfw);
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
    LogDebug("CherryEngine::Engine::Engine - Window Created\n");

    glfwMakeContextCurrent(m_window);
    // GLEW is a per-context library -> Call glewInit() every time the context switches!
    GLenum err;
    if((err = glewInit()) != GLEW_OK)
    {
        throw Exception("Error initializing GLEW (%d): %s\n", err,
            glewGetErrorString(err));
    }
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(errCallbackGl, NULL);

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
        if(glfwGetCurrentContext != m_window)
        {
            glfwMakeContextCurrent(m_window);
            GLenum err;
            if((err = glewInit()) != GLEW_OK)
            {
                throw Exception("Error initializing GLEW (%d): %s\n", err,
                    glewGetErrorString(err));
            }
        }

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
    //Finish
}

}