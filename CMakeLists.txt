cmake_minimum_required(VERSION 3.10)

project(newton)

add_executable(newton main.cpp)

install(TARGETS newton RUNTIME DESTINATION bin)
