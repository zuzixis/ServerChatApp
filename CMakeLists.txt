cmake_minimum_required(VERSION 3.7)
project(Server_ChatAPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(Server_ChatAPP main.cpp models/User.cpp models/User.h)
