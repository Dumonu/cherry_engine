cmake_minimum_required(VERSION 3.13.0)

execute_process(COMMAND git log -n1 --pretty=format:%h OUTPUT_VARIABLE LAST_COMMIT)

project(CherryEngine VERSION 0.0.0)

set(CherryEngine_VERSION_TWEAK 0x${LAST_COMMIT})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(CherryEngine)
add_subdirectory(src)