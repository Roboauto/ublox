cmake_minimum_required(VERSION 2.8.3)
project(ublox_msgs)

add_library(ublox_msgs src/ublox_msgs.cpp)

add_subdirectory(../ublox_serialization ublox_serialization)

target_link_libraries(ublox_msgs PUBLIC
    ublox_serialization)

target_include_directories(ublox_msgs PUBLIC
    PUBLIC gen/include include)

set_property(TARGET ublox_msgs PROPERTY POSITION_INDEPENDENT_CODE ON)
