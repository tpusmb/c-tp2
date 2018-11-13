cmake_minimum_required(VERSION 3.12)
project(Tp2_c)

set(CMAKE_CXX_STANDARD 14)

add_executable(Tp2_c Image2D.h Color.hpp Image2DWriter.h Image2DReader.h Accessor.h save-green-channel.cpp)