cmake_minimum_required(VERSION 3.20)
project(openGL)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#Find system-installed GLFW AND OpenGL
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

#GLAD is not a system library-we compile its .c file directly into our 
#executable
add_executable(wind wind.cpp glad/src/glad.c)

#Tell the compiler where glad.h and KHR/khrplatform.h live
target_include_directories(wind PRIVATE glad/include)

#Link against GLFW and OpenGL, plus dl (GLAD needs it on Linux)
target_link_libraries(wind PRIVATE glfw OpenGL::GL dl)