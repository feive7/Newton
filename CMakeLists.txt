cmake_minimum_required(VERSION 3.10)

project(newton)

if(WIN32)
set(raylib_DIR "../Libraries/raylib")
set(box2d_DIR "../Libraries/box2d")
endif()

find_package(raylib)
find_package(box2d)
add_executable(newton main.cpp)
target_link_libraries(newton raylib)
target_link_libraries(newton box2d)

install(TARGETS newton RUNTIME DESTINATION bin)
