configure_file(version.h.in version.h)
target_sources(CherryEngine PRIVATE
    log.h
    helpers.h
    Exception.h
    version.h

    log.cpp
    helpers.cpp
    Exception.cpp
)

# We configured a file, so we have to tell things where to look
target_include_directories(CherryEngine PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(CherryEngine PUBLIC "${CMAKE_CURRENT_SOURCE}")