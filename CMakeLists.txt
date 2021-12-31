cmake_minimum_required(VERSION 3.15)
project(login_system)

set(CMAKE_CXX_STANDARD 17)

add_executable(main src/initialize.cpp src/main.cpp)

target_link_libraries(main -lsqlite3)
