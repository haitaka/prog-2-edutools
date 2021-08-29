cmake_minimum_required(VERSION 3.20)

project(global-First_class-theory)

set(CMAKE_CXX_STANDARD 17)

# Files from `./src` directory
set(SRC
        src/fraction.cpp)


# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run ${SRC})