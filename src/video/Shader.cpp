#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <cstdarg>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Exception.h"
#include "log.h"
#include "helpers.h"
#include "Shader.h"

namespace CherryEngine
{

internal_shader::internal_shader(GLenum shaderType, const char* filename)
{
    LogDebug("Loading %s Shader\n", openglShaderTypeStr(shaderType));

    // open file
    std::ifstream in(filename);
    if(!in)
    {
        throw Exception("Error opening %s\n", filename);
    }
    // read file into string
    std::ostringstream ss;
    ss << in.rdbuf();
    // get c string
    std::string str = ss.str();
    const char* text = str.c_str();

    // create shader
    m_shader = glCreateShader(shaderType);
    if(m_shader == 0)
    {
        GLenum err = glGetError();
        throw Exception("Error creating shader (%d): %s", err, openglErrorStr(err));
    }

    // attach source to shader and compile
    glShaderSource(m_shader, 1, &text, NULL);
    glCompileShader(m_shader);

    // ensure successful compilation
    GLint result;
    glGetShaderiv(m_shader, GL_COMPILE_STATUS, &result);
    if(result != GL_TRUE)
    {
        glGetShaderiv(m_shader, GL_INFO_LOG_LENGTH, &result);
        char* buff = new char[result];
        glGetShaderInfoLog(m_shader, result, NULL, buff);
        glDeleteShader(m_shader);
        m_shader = 0;

        Exception e("Error compiling shader %s:\n%s", filename, buff);
        delete[] buff;
        throw e;
    }
}

internal_shader::~internal_shader()
{
    if(m_shader != 0)
    {
        glDeleteShader(m_shader);
        m_shader = 0;
    }
}

// Only allow move operations -> no double freeing
internal_shader::internal_shader(internal_shader&& other) : m_shader(other.m_shader)
{
    other.m_shader = 0;
}

internal_shader& internal_shader::operator=(internal_shader&& other)
{
    if(this != &other)
    {
        if(m_shader != 0)
        {
            glDeleteShader(m_shader);
            m_shader = 0;
        }
        std::swap(m_shader, other.m_shader);
    }
    return *this;
}

internal_program::internal_program(const std::vector<std::shared_ptr<internal_shader>>& shaders)
{
    LogDebug("Creating Program\n");
    // Create shader program
    m_program = glCreateProgram();
    if(m_program == 0)
    {
        GLenum err = glGetError();
        throw Exception("Error creating Shader Program (%d): %s",
                        err, openglErrorStr(err));
    }

    // attach all shaders
    for(auto shd : shaders)
    {
        glAttachShader(m_program, shd->m_shader);
        GLenum err = glGetError();
        if(err != GL_NO_ERROR)
        {
            glDeleteProgram(m_program);
            throw Exception("Error attaching shader %d (%d): %s",
                            shd->m_shader, err, openglErrorStr(err));
        }
    }

    // link the program
    glLinkProgram(m_program);

    // check whether link successful
    GLint result;
    glGetProgramiv(m_program, GL_LINK_STATUS, &result);
    if(result != GL_TRUE)
    {
        glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &result);
        char* buff = new char[result];
        glGetProgramInfoLog(m_program, result, NULL, buff);
        glDeleteProgram(m_program);
        m_program = 0;
    
        Exception e("Error linking shader program:\n%s", buff);
        delete[] buff;
        throw e;
    }

    // detach shaders
    for(auto shd : shaders)
    {
        glDetachShader(m_program, shd->m_shader);
    }
}

internal_program::~internal_program()
{
    if(m_program != 0)
    {
        glDeleteProgram(m_program);
        m_program = 0;
    }
}

internal_program::internal_program(internal_program&& other) : m_program(other.m_program)
{
    other.m_program = 0;
}

internal_program& internal_program::operator=(internal_program&& other)
{
    if(this != &other)
    {
        if(m_program != 0)
        {
            glDeleteProgram(m_program);
            m_program = 0;
        }
        std::swap(m_program, other.m_program);
    }
    return *this;
}

Shader::Shader(size_t shadercnt, ...)
{
    std::va_list args;
    va_start(args, shadercnt);

    for(int i = 0; i < shadercnt; ++i)
    {
        GLenum type = va_arg(args, GLenum);
        const char* filename = va_arg(args, const char*);
        m_shaders.push_back(std::make_shared<internal_shader>(type, filename));
    }

    m_program = std::make_shared<internal_program>(m_shaders);
}

}