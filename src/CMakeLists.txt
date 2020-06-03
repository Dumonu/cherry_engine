configure_file(version.h.in version.h)
target_sources(CherryEngine PRIVATE main.cpp version.h)

target_include_directories(CherryEngine PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")