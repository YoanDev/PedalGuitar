cmake_minimum_required(VERSION 3.13)
project(PedalGuitar C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 ")

#find_package(CURL REQUIRED)

add_executable(PedalGuitar main.c)

#include_directories(${CURL_INCLUDE_DIR})

target_link_libraries(PedalGuitar PRIVATE jack)
target_link_libraries(PedalGuitar PRIVATE m)
target_link_libraries(PedalGuitar PRIVATE pthread)








