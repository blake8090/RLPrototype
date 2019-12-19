
file(GLOB SDL2_SEARCH_PATHS
    "${PROJECT_LIB_DIR}/SDL2-*"
    "${PROJECT_LIB_DIR}/sdl2-*"
    "${PROJECT_LIB_DIR}/sdl2"
    "${SDL2_ROOT}"
    "$ENV{SDL2_ROOT}"
    "/usr/local/"
    "/usr/"
    "/sw/"
    "/opt/local/"
    "/opt/csw/"
    "/opt/"
)

find_path(SDL2_INCLUDE_DIR SDL.h
    PATH_SUFFIXES include/ sdl2/include
    PATHS ${SDL2_SEARCH_PATHS}
)

message("SDL2 includes found at: ${SDL2_INCLUDE_DIR}.")

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_LIB_BUILD "x64")
else()
    set(SDL2_LIB_BUILD "x86")
endif()

message("Searching for SDL2 libraries (${SDL2_LIB_BUILD})")

find_library(SDL2_LIBRARY
    NAMES SDL2
    PATH_SUFFIXES lib/ lib/x86_64-linux-gnu/ lib64/ lib/${SDL2_LIB_BUILD}
    PATHS "${SDL2_SEARCH_PATHS}"
    "${SDL2_ROOT}"
    "$ENV{SDL2_ROOT}"
    "/usr/local/"
    "/usr/"
    "/sw/"
    "/opt/local/"
    "/opt/csw/"
    "/opt/"
    "/usr/lib/x86_64-linux-gnu"
)

message("SDL2 libraries found at ${SDL2_LIBRARY}.")

set(SDL2_LIBRARIES ${SDL2_LIBRARY})

MARK_AS_ADVANCED(
    SDL2_SEARCH_PATHS,
    SDL2_INCLUDE_DIR,
    SDL2_LIB_BUILD,
    SDL2_LIBRARY,
)
