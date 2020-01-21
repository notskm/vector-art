cmake_minimum_required(VERSION 3.15)

project(vector-art)

set(
    CMAKE_MODULE_PATH
    ${CMAKE_BINARY_DIR}
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)

set(CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR} ${CMAKE_PREFIX_PATH})

include(run-conan)

add_subdirectory(external)
add_subdirectory(src)
