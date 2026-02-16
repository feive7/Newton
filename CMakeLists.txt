cmake_minimum_required(VERSION 3.10)

project(newton)

find_package(box2d)
add_executable(newton main.cpp)
target_link_libraries(newton box2d)

install(TARGETS newton RUNTIME DESTINATION bin)
