cmake_minimum_required(VERSION 3.5)

project(sys_sol LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(sys_sol main.cpp
    object.h object.cpp
    renderer.h renderer.cpp
    camera.h camera.cpp
    shader.h shader.cpp
    uvbuffer.h uvbuffer.cpp
    vertexarray.h vertexarray.cpp
    vertexbuffer.h vertexbuffer.cpp
    controls.h controls.cpp
    navigationcontrols.h navigationcontrols.cpp
    texture.h texture.cpp
    fpscontrols.h fpscontrols.cpp
    stb_image/stb_image.h stb_image/stb_image.cpp
    pointlight.h pointlight.cpp)

target_link_libraries(sys_sol glfw GLEW libGLEW.so libGLU.so libGL.so)
