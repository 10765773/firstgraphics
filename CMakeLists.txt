cmake_minimum_required(VERSION 3.23)
project(firstgraphics)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    find_package(SDL2 REQUIRED)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(SDL2_INCLUDE_DIRS C:/libs/SDL/include)
    set(SDL2_LIB_DIR C:/libs/SDL/lib/x64)
endif()

include_directories(${SDL2_INCLUDE_DIRS})
link_directories(${SDL2_LIB_DIR})

add_executable(${PROJECT_NAME} src/main.cpp src/glad.c src/glad.h src/shader.h)
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
