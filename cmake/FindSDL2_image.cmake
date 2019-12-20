
file(GLOB SDL2_IMAGE_SEARCH_PATHS
    "${PROJECT_LIB_DIR}/SDL2_image-*"
    "${PROJECT_LIB_DIR}/sdl2_image-*"
    "${PROJECT_LIB_DIR}/sdl2_image"
    "${SDL2_IMAGE_ROOT}"
    "$ENV{SDL2_IMAGE_ROOT}"
    "/usr/local/"
    "/usr/"
    "/sw/"
    "/opt/local/"
    "/opt/csw/"
    "/opt/"
)

find_path(SDL2_IMAGE_INCLUDE_DIR SDL_image.h
    PATH_SUFFIXES include/ include/SDL2
    PATHS ${SDL2_IMAGE_SEARCH_PATHS}
)

message("\nSDL2_image includes found at: ${SDL2_IMAGE_INCLUDE_DIR}.")

if (${CMAKE_SIZEOF_VOID_P} MATCHES 8)
    set(SDL2_IMAGE_LIB_BUILD "x64")
else()
    set(SDL2_IMAGE_LIB_BUILD "x86")
endif()

message("Searching for SDL2_image libraries (${SDL2_IMAGE_LIB_BUILD})")

find_library(SDL2_IMAGE_LIBRARY
    NAMES SDL2_image
    PATH_SUFFIXES lib/ lib/x86_64-linux-gnu/ lib64/ lib/${SDL2_IMAGE_LIB_BUILD}
    PATHS "${SDL2_IMAGE_SEARCH_PATHS}"
    "${SDL2_IMAGE_ROOT}"
    "$ENV{SDL2_IMAGE_ROOT}"
    "/usr/local/"
    "/usr/"
    "/sw/"
    "/opt/local/"
    "/opt/csw/"
    "/opt/"
    "/usr/lib/x86_64-linux-gnu"
)

message("SDL2_image libraries found at ${SDL2_IMAGE_LIBRARY}.\n")

set(SDL2_IMAGE_LIBRARIES ${SDL2_IMAGE_LIBRARY})

MARK_AS_ADVANCED(
    SDL2_IMAGE_SEARCH_PATHS,
    SDL2_IMAGE_INCLUDE_DIR,
    SDL2_IMAGE_LIB_BUILD,
    SDL2_IMAGE_LIBRARY,
)
