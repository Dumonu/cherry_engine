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

# Create an executable target - CherryEngine.exe
add_executable(CherryEngine)
add_subdirectory(src) # sources are in the src directory