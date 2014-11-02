cmake_minimum_required(VERSION 2.8)
project(X-IMU-API)

enable_testing()

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
  src/ximuapi/utils/fixed_float.cpp
  src/ximuapi/data/register_data.cpp
  src/ximuapi/data/datetime_data.cpp
  src/ximuapi/data/quaternion_data.cpp
  
)

# setup testing

# add c++ program
add_executable (PKT_ENC_TEST tests/packet_encoding_test.cpp)
add_executable (PKT_CNST_TEST tests/packet_construction_test.cpp)
add_executable (FXD_FLT_TEST tests/fixed_float_test.cpp)
add_executable (DATA_TYPES_TEST tests/data_types_test.cpp)


# link the x-IMU-API with the programs
target_link_libraries(PKT_ENC_TEST X-IMU-API)
target_link_libraries(PKT_CNST_TEST X-IMU-API)
target_link_libraries(FXD_FLT_TEST X-IMU-API)
target_link_libraries(DATA_TYPES_TEST X-IMU-API)

# perform the test
add_test(PACKET_ENCODING_DECODING PKT_ENC_TEST)
add_test(PACKET_CONSTRUCTION PKT_CNST_TEST)
add_test(FIXED_FLOAT FXD_FLT_TEST)
add_test(DATA_TYPES DATA_TYPES_TEST)