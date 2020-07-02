#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "helpers.h"

const char* str_GL_NO_ERROR = "No error";
const char* str_GL_INVALID_ENUM = "Invalid enum argument";
const char* str_GL_INVALID_VALUE = "Argument out of range";
const char* str_GL_INVALID_OPERATION = "Invalid operation";
const char* str_GL_INVALID_FRAMEBUFFER_OPERATION = "Framebuffer incomplete";
const char* str_GL_OUT_OF_MEMORY = "Out of memory";
const char* str_GL_STACK_UNDERFLOW = "Stack underflow";
const char* str_GL_STACK_OVERFLOW = "Stack overflow";
const char* str_unknown_err = "Unknown error";

const char* openglErrorStr(GLenum err)
{
    switch(err)
    {
    case GL_NO_ERROR:
        return str_GL_NO_ERROR;
    case GL_INVALID_ENUM:
        return str_GL_INVALID_ENUM;
    case GL_INVALID_VALUE:
        return str_GL_INVALID_VALUE;
    case GL_INVALID_OPERATION:
        return str_GL_INVALID_OPERATION;
    case GL_INVALID_FRAMEBUFFER_OPERATION:
        return str_GL_INVALID_FRAMEBUFFER_OPERATION;
    case GL_OUT_OF_MEMORY:
        return str_GL_OUT_OF_MEMORY;
    case GL_STACK_UNDERFLOW:
        return str_GL_STACK_UNDERFLOW;
    case GL_STACK_OVERFLOW:
        return str_GL_STACK_OVERFLOW;
    default:
        return str_unknown_err;
    }
}

const char* str_COMPUTE = "Compute";
const char* str_VERTEX = "Vertex";
const char* str_TESS_CONTROL = "Tessellation Control";
const char* str_TESS_EVALUATION = "Tessellation Evaluation";
const char* str_GEOMETRY = "Geometry";
const char* str_FRAGMENT = "Fragment";
const char* str_unknown_shd = "Unknown";

const char* openglShaderTypeStr(GLenum shaderType)
{
    switch (shaderType)
    {
    case GL_COMPUTE_SHADER:
        return str_COMPUTE;
    case GL_VERTEX_SHADER:
        return str_VERTEX;
    case GL_TESS_CONTROL_SHADER:
        return str_TESS_CONTROL;
    case GL_TESS_EVALUATION_SHADER:
        return str_TESS_EVALUATION;
    case GL_GEOMETRY_SHADER:
        return str_GEOMETRY;
    case GL_FRAGMENT_SHADER:
        return str_FRAGMENT;
    default:
        return str_unknown_shd;
    }
}