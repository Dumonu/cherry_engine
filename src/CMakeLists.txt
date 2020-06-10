target_sources(CherryEngine PRIVATE
    CherryEngine.h
    settings.h
    setting_names.h

    main.cpp
    CherryEngine.cpp
)

# We configured a file, so we have to tell things where to look
target_include_directories(CherryEngine PUBLIC "${CMAKE_CURRENT_BINARY_DIR}")
target_include_directories(CherryEngine PUBLIC "${CMAKE_CURRENT_SOURCE}")

add_subdirectory(util)