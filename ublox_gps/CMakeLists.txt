cmake_minimum_required(VERSION 2.8.3)
project(ublox_gps)

add_subdirectory(../ublox_msgs ublox_msgs)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
    BASIC_SETUP CMAKE_TARGETS
    BUILD missing)

# build library
add_library(ublox_gps
    src/gps.cpp
    src/mkgmtime.cpp)

# include other ublox packages
target_include_directories(ublox_gps
    PUBLIC ${PROJECT_SOURCE_DIR}/include
    PUBLIC ${PROJECT_SOURCE_DIR}/../ublox_serialization/include)

message(archi:${ARCHITECTURE})

target_link_libraries(ublox_gps
  pthread
  ublox_msgs
)
