configure_file(version.h.in version.h)
target_sources(CherryEngine PRIVATE main.cpp version.h)

# We configured a file, so we have to tell things where to look
target_include_directories(CherryEngine PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")