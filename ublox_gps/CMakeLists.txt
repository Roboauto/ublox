cmake_minimum_required(VERSION 3.13)
project(ublox_gps)

add_subdirectory(../ublox_msgs ublox_msgs)

# build library
add_library(ublox_gps
    src/gps.cpp
    src/mkgmtime.cpp
    src/callback.cpp)

# include other ublox packages
target_include_directories(ublox_gps PUBLIC
    PUBLIC ${PROJECT_SOURCE_DIR}/include)

if(NOT MSVC)
    set(DEPENDENCIES 
        pthread)
endif()

target_link_libraries(ublox_gps PUBLIC
    ${DEPENDENCIES}
    ublox_msgs
)

set_property(TARGET ublox_gps PROPERTY POSITION_INDEPENDENT_CODE ON)
