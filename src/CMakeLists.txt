cmake_minimum_required(VERSION 3.9)

project(RLPrototype)

set(PROJECT_LIB_DIR "${PROJECT_SOURCE_DIR}/../lib")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/../cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

add_library(game_lib STATIC
    game.cpp
    assets.cpp
    sdl_wrapper.cpp
)
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
# target_link_libraries(${CMAKE_PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(${CMAKE_PROJECT_NAME} game_lib ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_PREFIX})
