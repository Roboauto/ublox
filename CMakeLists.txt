cmake_minimum_required(VERSION 3.4)
project(ublox)

find_package(Boost COMPONENTS REQUIRED thread)

add_subdirectory(ublox_gps)

if(BUILDSTANDALONE)
    set (CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/libs/robo_core)

    find_package("RoboCore")

endif()
RoboCore_requirePlugin("RoboCore::Sensors")

set(SOURCE_LIST
    ublox/src/ublox.cpp
    ublox/src/Product/HpPosRec.cpp
    ublox/src/Product/HpgRef.cpp
    ublox/src/Product/AdrUdr.cpp
    ublox/src/Firmware/Firmware8.cpp)

RoboCore_generateStaticSharedLib(
    TARGET ublox
    STATIC_TARGET_ONLY
    SOURCES ${SOURCE_LIST}
    INCLUDES ${PROJECT_SOURCE_DIR}/ublox/include
    RC_LINK_LIBS
        RoboCore::Sensors
    LINK_LIBS
        ublox_gps
        ${Boost_LIBRARIES}
)

RoboCore_install(ublox
    INCLUDES ${PROJECT_SOURCE_DIR}/ublox/include
    REQUIRE_PLUGINS RoboCore::Sensors
    CONAN_FILE ${PROJECT_SOURCE_DIR}/ublox_gps/conanfile.txt
    README ${PROJECT_SOURCE_DIR}/README.md
)