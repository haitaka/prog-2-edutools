cmake_minimum_required(VERSION 3.20)

project(global-Input_output-Hello_world)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME}-hello src/hello.cpp)
add_executable(${PROJECT_NAME}-ioc src/io.c)
add_executable(${PROJECT_NAME}-iocpp src/io.cpp)
add_executable(${PROJECT_NAME}-namespaces src/namespaces.cpp)
