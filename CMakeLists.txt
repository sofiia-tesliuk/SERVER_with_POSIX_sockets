cmake_minimum_required(VERSION 3.13)
project(server_with_posix_sockets)

set(CMAKE_CXX_STANDARD 17)

add_executable(server server.cpp)
add_executable(client client.cpp)