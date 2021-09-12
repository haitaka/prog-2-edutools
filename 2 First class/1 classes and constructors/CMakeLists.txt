cmake_minimum_required(VERSION 3.20)

project(global-2_First_class-1_classes_and_constructors)

set(CMAKE_CXX_STANDARD 17)

# Files from `./src` directory
set(SRC src/fraction.cpp)


# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run ${SRC})