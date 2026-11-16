cmake_minimum_required(VERSION 3.1)

project(glew)

set(CMAKE_CXX_STANDARD 14)

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${PROJECT_NAME} STATIC
        "${CMAKE_CURRENT_SOURCE_DIR}/src/glew.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/glewinfo.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/visualinfo.c")

