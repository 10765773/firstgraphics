cmake_minimum_required(VERSION 3.23)
project(firstgraphics)

set(CMAKE_CXX_STANDARD 14)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(firstgraphics main.cpp)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
