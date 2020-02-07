cmake_minimum_required(VERSION 3.13)
project(ublox CXX)

find_package(Boost COMPONENTS REQUIRED thread)

set(CMAKE_CXX_STANDARD 17)

if (${CMAKE_CXX_COMPILER} MATCHES ".*aarch64.*")
    set(ARCHITECTURE aarch64)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=armv8-a+crypto+crc -mtune=cortex-a57")
else ()
    set(ARCHITECTURE x86_64)
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native -mtune=native")
endif ()

if(BUILD_STANDALONE)
    set(RoboCore_DIR /usr/local)
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${RoboCore_DIR}/cmake)
    find_package("RoboCore")

    RoboCore_setConanProfile(${PROJECT_SOURCE_DIR}/conan_profiles/${ARCHITECTURE}/${CMAKE_CXX_COMPILER_ID}-${COMPILER_VERSION_MAJOR})
endif()

add_subdirectory(ublox_gps)

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
    INCLUDES
        ${PROJECT_SOURCE_DIR}/ublox/include/
        ${PROJECT_SOURCE_DIR}/ublox_gps/include/
        ${PROJECT_SOURCE_DIR}/ublox_msgs/include/
        ${PROJECT_SOURCE_DIR}/ublox_msgs/gen/include/
        ${PROJECT_SOURCE_DIR}/ublox_serialization/include/
    TARGETS ublox_gps ublox_msgs
    REQUIRE_PLUGINS RoboCore::Sensors
    REQUIRES ublox_gps ublox_msgs ${Boost_LIBRARIES}
    CONAN_FILE ${PROJECT_SOURCE_DIR}/ublox_gps/conanfile.txt
    README ${PROJECT_SOURCE_DIR}/README.md
)
