cmake_minimum_required(VERSION 3.13 FATAL_ERROR)

set(PROJECT_NAME fsm)

project(${PROJECT_NAME} LANGUAGES CXX)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME})
