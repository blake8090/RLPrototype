cmake_minimum_required(VERSION 3.5)

project(RLPrototype)

set(PROJECT_LIB_DIR "${PROJECT_SOURCE_DIR}/lib")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(${SDL2_INCLUDE_DIR} ${SDL2_IMAGE_INCLUDE_DIR})

add_subdirectory(src)
add_subdirectory(test)
