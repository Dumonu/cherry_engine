#ifndef SHADER_H_06122020
#define SHADER_H_06122020

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "global.h"

namespace CherryEngine
{

// FOR INTERNAL USE ONLY
class EXPORT internal_shader
{
    GLuint m_shader = 0;
    friend class internal_program;
    friend class Shader;

public:
    internal_shader(GLenum shaderType, const char* filename);
    ~internal_shader();
    internal_shader(const internal_shader&) = delete;
    internal_shader& operator=(const internal_shader&) = delete;
    internal_shader(internal_shader&& other);
    internal_shader& operator=(internal_shader&& other);
};

// FOR INTERNAL USE ONLY
class EXPORT internal_program
{
    GLuint m_program = 0;
    friend class Shader;

public:
    internal_program(const std::vector<std::shared_ptr<internal_shader>>& shaders);
    ~internal_program();
    internal_program(const internal_program&) = delete;
    internal_program& operator=(const internal_program&) = delete;
    internal_program(internal_program&& other);
    internal_program& operator=(internal_program&& other);

};

// Manages a shader program
// It is safe to copy the Shader because it uses a shared_ptr to manage the program
class EXPORT Shader
{
    std::shared_ptr<internal_program> m_program;
    std::vector<std::shared_ptr<internal_shader>> m_shaders;

public:
    // To use:
    // shadercnt - number of shaders being passed
    // For each shader:
    //     GLenum type
    //     const char* filename
    Shader(size_t shadercnt, ...);
};

}

#endif