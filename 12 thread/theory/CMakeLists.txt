cmake_minimum_required(VERSION 3.20)

project(global-12_thread-theory)

set(CMAKE_CXX_STANDARD 20)

find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME}-run src/0-threads.cpp)
target_link_libraries(${PROJECT_NAME}-run Threads::Threads)

add_executable(${PROJECT_NAME}-1-counter src/1-counter.cpp)
target_link_libraries(${PROJECT_NAME}-1-counter Threads::Threads)

add_executable(${PROJECT_NAME}-2-prod-cons-err src/2-prod-cons-err.cpp)
target_link_libraries(${PROJECT_NAME}-2-prod-cons-err Threads::Threads)

add_executable(${PROJECT_NAME}-3-prod-cons-mutex src/3-prod-cons-mutex.cpp)
target_link_libraries(${PROJECT_NAME}-3-prod-cons-mutex Threads::Threads)

add_executable(${PROJECT_NAME}-4-prod-cons-raii src/4-prod-cons-raii.cpp)
target_link_libraries(${PROJECT_NAME}-4-prod-cons-raii Threads::Threads)

add_executable(${PROJECT_NAME}-5-deadlock src/5-deadlock.cpp)
target_link_libraries(${PROJECT_NAME}-5-deadlock Threads::Threads)

add_executable(${PROJECT_NAME}-6-cond-var src/6-cond-var.cpp)
target_link_libraries(${PROJECT_NAME}-6-cond-var Threads::Threads)
