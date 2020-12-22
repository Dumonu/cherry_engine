# 3.13 changes target_sources() to take paths relative to CURRENT_SOURCE_DIR
cmake_minimum_required(VERSION 3.13.0)

# General Compilation Flags
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Track my last commit to generate the TWEAK part of the version number
execute_process(COMMAND git log -n1 --pretty=format:%h OUTPUT_VARIABLE LAST_COMMIT)

# Create the CherryEngine Project
project(CherryEngine VERSION 0.0.0)
set(CherryEngine_VERSION_TWEAK 0x${LAST_COMMIT})

# Libraries
find_package(glfw3 3.3 REQUIRED)
find_package(GLEW REQUIRED)

function(arch_def tgt)
    if(CMAKE_SYSTEM_NAME STREQUAL Windows)
        # SUPPORTED
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_WIN32)
    elseif(CMAKE_SYSTEM_NAME STREQUAL Darwin)
        # PLAN TO SUPPORT
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_MACOSX)
    elseif(CMAKE_SYSTEM_NAME STREQUAL Linux)
        # SUPPORTED
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_LINUX)
    elseif(CMAKE_SYSTEM_NAME STREQUAL Android)
        # NOT SUPPORTED
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_ANDROID)
    elseif(CMAKE_SYSTEM_NAME STREQUAL FreeBSD)
        # NOT SUPPORTED
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_FREEBSD)
    elseif(CMAKE_SYSTEM_NAME STREQUAL CrayLinuxEnvironment)
        # NOT SUPPORTED
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_CRAY)
    elseif(CMAKE_SYSTEM_NAME STREQUAL MSYS)
        # NOT SUPPORTED
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_MSYS)
    else()
        target_compile_definitions(${tgt} PRIVATE CE_PLAT_UNKNOWN)
    endif()

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        target_compile_definitions(${tgt} PRIVATE CE_ARCH_64BIT)
    else()
        target_compile_definitions(${tgt} PRIVATE CE_ARCH_32BIT)
    endif()
endfunction()

# Create an executable target - CherryEngine.exe
add_library(CherryEngine SHARED)
add_subdirectory(src)  # sources are in the src directory
add_subdirectory(test) # test files are in the test directory

# Add compiler warnings
if(MSVC)
    target_compile_options(CherryEngine PRIVATE /W4)
else()
    target_compile_options(CherryEngine PRIVATE -Wall -Wextra -pedantic)
    target_link_libraries(CherryEngine GL GLU) # required for linking on Linux, but not necessarily Windows
endif()

arch_def(CherryEngine)

target_compile_definitions(CherryEngine PRIVATE CE_BUILDING_LIB)
target_link_libraries(CherryEngine glfw GLEW::GLEW)