cmake_minimum_required(VERSION 3.15)
project(theGame C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add vendor libraries as subdirectories (assuming they are CMake-ready)
add_subdirectory(vendor/raylib)
add_subdirectory(vendor/enet)

# Add your source files
file(GLOB_RECURSE SOURCES src/*.c)

# Define the executable
add_executable(theGame ${SOURCES}
        include/player.h
        src/player.c
        include/input.h
        include/physics.h
        src/physics.c)

# Include paths
target_include_directories(theGame PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/vendor/raylib/src   # This is where raylib.h lives when built from source
        ${CMAKE_SOURCE_DIR}/vendor/raylib/src/external
)


# Link against the Raylib and ENet targets
target_link_libraries(theGame PRIVATE raylib enet)

# Required for Raylib (platform-specific dependencies)
if(UNIX AND NOT APPLE)
    target_link_libraries(theGame PRIVATE m pthread dl rt X11)
elseif(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKIT_LIBRARY IOKit)
    find_library(CoreVideo_LIBRARY CoreVideo)
    target_link_libraries(theGame PRIVATE ${COCOA_LIBRARY} ${OpenGL_LIBRARY} ${IOKIT_LIBRARY} ${CoreVideo_LIBRARY})
endif()
