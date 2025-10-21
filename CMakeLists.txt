cmake_minimum_required(VERSION 3.14)

project(APP_RETI_01_4INA_Saverione_Pierpaolo)

# Try to find a locally installed raylib, but don't quit on fail
find_package(raylib 5.5 QUIET)

# This code downloads raylib into a directory called _deps and adds it as a subdirectory, compiling it with the program when running the build command
include(FetchContent)
if (NOT raylib_FOUND)
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.5.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP True #This option is not required but suppresses a warning
    )
    FetchContent_MakeAvailable(raylib)
endif()

#MY_DIRS
include_directories(App)
include_directories(Core)

# We don't want raylib's examples built. This option is picked up by raylib's CMakeLists.txt
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

#EXECUTABLE
add_executable(${PROJECT_NAME} App/main.cpp
    Core/Window.h
    Core/Window.cpp
    Core/TextCase.h
    Core/TextCase.cpp
    Core/Button.h
    Core/Button.cpp
    App/Application.h
    App/Application.cpp
    App/functions.h
    App/functions.cpp
)

# Link raylib to project
target_link_libraries(${PROJECT_NAME} 
    raylib
)
# Make project find the <raylib.h> header (and others)
target_include_directories(${PROJECT_NAME} PUBLIC "${raylib_SOURCE_DIR}/src")

#COMPILER OPTION
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
