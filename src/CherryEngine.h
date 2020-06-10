#ifndef CHERRYENGINE_H_06042020
#define CHERRYENGINE_H_06042020

#include "settings.h"

namespace CherryEngine {

class Engine {
//  Input::Subsystem m_input;
//  Audio::Subsystem m_audio;
//  Video::Subsystem m_video;

    int m_settings[S_NUM + 1];

public:
    // Constructors
    Engine();
    Engine(const char* settingsfile);

    ~Engine();
};

}

#endif