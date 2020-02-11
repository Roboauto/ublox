cmake_minimum_required(VERSION 3.13)
project(ublox CXX)

set(RoboCore_PATH "/usr/local" CACHE STRING "Path to RoboCORE installation (folder with plugins and cmake folder)")

if (BUILD_STANDALONE)
    set (CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${RoboCore_PATH}/cmake)
    find_package("RoboCore")

    RoboCore_setArchitecture(ARCHITECTURE)
    RoboCore_setConanProfile(${PROJECT_SOURCE_DIR}/conan_profiles/${ARCHITECTURE}/${CMAKE_CXX_COMPILER_ID}-${COMPILER_VERSION_MAJOR})
endif ()

RoboCore_createPlugin(ublox ublox)

set(CMAKE_CXX_STANDARD 17)

RoboCore_requirePlugin("RoboCore::Sensors")

RoboCore_conanRequire(conanfile.txt)

add_subdirectory(ublox_gps)


find_package(Boost COMPONENTS REQUIRED thread)

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
    CONAN_PKG::spdlog
    CONAN_PKG::msgpack
    CONAN_PKG::yaml-cpp
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
    CONAN_FILE ${PROJECT_SOURCE_DIR}/conanfile.txt
    README ${PROJECT_SOURCE_DIR}/README.md
)
