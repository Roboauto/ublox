



RoboCore_requirePlugin(RoboCore::RTK)

add_executable( UbloxGPSExample
        main.cpp
        )

target_link_libraries(UbloxGPSExample
        ublox
        RoboCore::RTK)