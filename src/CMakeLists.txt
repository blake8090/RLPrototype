cmake_minimum_required(VERSION 3.9)

project(RLPrototype)

set(PROJECT_LIB_DIR "${PROJECT_SOURCE_DIR}/../lib")

# Searches for the SDL2 library on a Windows system.
# SDL2 is expected to be found in the "lib" subdirectory
# TODO: make proper FindSDL2 cmake file
function(find_sdl2_win)
    file(GLOB SDL2_DIRECTORY
        "${PROJECT_LIB_DIR}/SDL2*"
        "${PROJECT_LIB_DIR}/sdl2*"
        "${SDL2_ROOT}"
        "$ENV{SDL2_ROOT}"
    )

    FIND_PATH(SDL2_INCLUDE_DIR SDL.h
        PATH_SUFFIXES include/ sdl2/include
        PATHS ${SDL2_DIRECTORY}
    )
    message("---\nSDL2 includes found at: '${SDL2_INCLUDE_DIR}'.\n")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_LIB_TYPE "x64")
    else()
        set(SDL2_LIB_TYPE "x86")
    endif()

    message("Searching for SDL2 libraries (${SDL2_LIB_TYPE})\n")
    find_library(SDL2_LIBRARIES
        NAMES SDL2
        PATHS ${SDL2_DIRECTORY}/lib/${SDL2_LIB_TYPE}
    )
    message("SDL2 libraries found at: '${SDL2_LIBRARIES}'.\n")
endfunction()

# Searches for the SDL2 image library on a Windows system.
# SDL2 is expected to be found in the "lib" subdirectory
# TODO: make proper FindSDL2 cmake file
function(find_sdl2_image_win)
    file(GLOB SDL2_IMG_DIRECTORY
        "${PROJECT_LIB_DIR}/SDL2_image*"
        "${PROJECT_LIB_DIR}/sdl2_image*"
        "${SDL2_ROOT}"
        "$ENV{SDL2_ROOT}"
    )

    FIND_PATH(SDL2_IMG_INCLUDE_DIR SDL_image.h
        PATH_SUFFIXES include/
        PATHS ${SDL2_IMG_DIRECTORY}
    )
    message("---\nSDL2 image includes found at: '${SDL2_IMG_INCLUDE_DIR}'.\n")

    if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
        set(SDL2_IMG_LIB_TYPE "x64")
    else()
        set(SDL2_IMG_LIB_TYPE "x86")
    endif()

    message("Searching for SDL2 image libraries (${SDL2_IMG_LIB_TYPE})\n")
    find_library(SDL2_IMG_LIBRARIES
        NAMES SDL2_image
        PATHS ${SDL2_IMG_DIRECTORY}/lib/${SDL2_IMG_LIB_TYPE}
    )
    message("SDL2 image libraries found at: '${SDL2_IMG_LIBRARIES}'.\n")
endfunction()

if (WIN32)
    find_sdl2_win()
    find_sdl2_image_win()
else()
    find_package(SDL2 REQUIRED)
    find_package(SDL2_image REQUIRED)
endif()
include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMG_INCLUDE_DIR})

add_library(game_lib STATIC
    game.cpp
    assets.cpp
    sdl_wrapper.cpp
)
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMG_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} game_lib)

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
