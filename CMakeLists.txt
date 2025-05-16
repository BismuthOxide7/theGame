cmake_minimum_required(VERSION 3.15)
project(theGame C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/vendor/raylib/include
    ${CMAKE_SOURCE_DIR}/vendor/enet/include
)

# Library directories
link_directories(
    ${CMAKE_SOURCE_DIR}/vendor/raylib/lib
    ${CMAKE_SOURCE_DIR}/vendor/enet/lib
)

# Source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.c)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link with static libraries
target_link_libraries(${PROJECT_NAME} raylib enet m)

# Linux-specific dependencies
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} pthread dl rt X11)
endif()
