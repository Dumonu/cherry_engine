# CherryEngine

A general purpose game engine.

## Goals
- Export API to C++ files through a shared library
- Support the following workflow:
    1. Create a `CherryEngine::Engine` object
    2. Add game objects to the engine
    3. Add runnables with an `init()` and `update()` function to the engine
    4. Call `CherryEngine::Engine::Start()` to run the game
- Abstract away OpenGL's breaking of the rule of 0/3/5
- Support Input Queuing (as would be required for fighting game style command inputs)
- Support audio mixing

## Stretch Goals
- Incorporate something like ImGUI for game prototyping
- Create an editor GUI that generates scene C++ files
    - call a `startScene(CherryEngine::Engine&)` function or the like
