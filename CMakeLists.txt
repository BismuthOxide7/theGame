cmake_minimum_required(VERSION 3.15)
project(my_fps_game C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add Raylib and ENet
add_subdirectory(vendor/raylib)
add_subdirectory(vendor/enet)

# Include paths
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vendor/raylib/src
    ${CMAKE_SOURCE_DIR}/vendor/enet/include
)

# Define sources
file(GLOB_RECURSE SOURCES src/*.c)

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} raylib enet m)

# OS-specific: Link extra libs for Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} pthread dl rt X11)
endif()
