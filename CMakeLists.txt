cmake_minimum_required(VERSION 3.4)
project(ublox)

add_subdirectory(ublox_gps)

add_library(ublox
    ublox/src/ublox.cpp
    ublox/src/Product/HpPosRec.cpp
    ublox/src/Product/HpgRef.cpp
    ublox/src/Product/AdrUdr.cpp
    ublox/src/Firmware/Firmware8.cpp)

RoboCore_requirePlugin("RoboCore::Sensors")

target_link_libraries(ublox
    ublox_gps
    RoboCore::Core
    RoboCore::Sensors
)

target_include_directories(ublox
    PUBLIC ublox/include)