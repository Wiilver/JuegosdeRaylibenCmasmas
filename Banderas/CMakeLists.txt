cmake_minimum_required(VERSION 3.11)

project(Banderas)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

add_executable(Banderas main.cpp)

target_link_libraries(Banderas raylib)