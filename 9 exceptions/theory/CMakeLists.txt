cmake_minimum_required(VERSION 3.20)

project(global-9_exceptions-theory)

set(CMAKE_CXX_STANDARD 20)

# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run src/main.cpp)
add_executable(${PROJECT_NAME}-example src/example.cpp)
