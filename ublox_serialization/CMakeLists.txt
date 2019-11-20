cmake_minimum_required(VERSION 2.8.3)

project(ublox_serialization)

add_library(ublox_serialization INTERFACE)

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
            "${CMAKE_BINARY_DIR}/conan.cmake")
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

target_include_directories(ublox_serialization
    INTERFACE include)

target_link_libraries(ublox_serialization
        INTERFACE CONAN_PKG::boost_utility)
