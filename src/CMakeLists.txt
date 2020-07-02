target_sources(CherryEngine PRIVATE
    CherryEngine.h
    settings.h
    setting_names.h

    main.cpp
    CherryEngine.cpp
)

target_include_directories(CherryEngine PUBLIC "${CMAKE_CURRENT_SOURCE}")

add_subdirectory(util)
add_subdirectory(video)