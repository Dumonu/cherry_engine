#ifndef CHERRYENGINE_H_06042020
#define CHERRYENGINE_H_06042020

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "global.h"
#include "settings.h"

namespace CherryEngine {

class EXPORT Engine {
    static int instances;

    int m_settings[S_NUM + 1];
    GLFWwindow* m_window;

//  Input::Subsystem m_input;
//  Audio::Subsystem m_audio;
//  Video::Subsystem m_video;

public:
    // Constructors
    Engine();
    Engine(const char* settingsfile);

    ~Engine();

    void Start();
};

}

#endif