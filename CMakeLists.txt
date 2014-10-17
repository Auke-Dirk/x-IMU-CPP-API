cmake_minimum_required(VERSION 2.8)
project(X-IMU-API)

set(X-IMU-API_MAJOR_VERION 0)
set(X-IMU-API_MINOR_VERION 1)
set(X-IMU-API_PATCH_VERION 0)

# set compiler flags
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11")

# set main include directory
include_directories(
  include # main include directory
)

# add functionality to the library
add_library(X-IMU-API STATIC
  src/ximuapi/packet/packet_encoding.cpp
)
