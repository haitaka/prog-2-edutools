cmake_minimum_required(VERSION 3.20)

project(global-2_First_class-2_destructors)

set(CMAKE_CXX_STANDARD 14)

# Files from `./src` directory
set(SRC src/main.cpp)

# Running learner side code
# Use PROJECT_NAME dependent names of targets for the plugin support to work correctly.
add_executable(${PROJECT_NAME}-run ${SRC})

# Compile in 32-bit mode
# to limit address space by 2G
# thus preventing system memory from exhaustion
set_target_properties(${PROJECT_NAME}-run PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")