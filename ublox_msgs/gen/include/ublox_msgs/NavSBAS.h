#pragma once

#include <array>
#include <vector>
#include "NavSBAS_SV.h"
#include <cstdint>

namespace ublox_msgs {
    struct NavSBAS {
        // NAV-SBAS (0x01 0x32);
        // SBAS Status Data
        //;
        // This message outputs the status of the SBAS sub system
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 50;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        
        uint8_t geo;               // PRN Number of the GEO where correction and integrity 
                                // data is used from;
        
        uint8_t mode;              // SBAS Mode
        static constexpr uint8_t MODE_DISABLED = 0;
        static constexpr uint8_t MODE_ENABLED_INTEGRITY = 1;
        static constexpr uint8_t MODE_ENABLED_TESTMODE = 3;
        
        int8_t sys;                // SBAS System (WAAS/EGNOS/...)
        static constexpr int8_t SYS_UNKNOWN = -1;
        static constexpr int8_t SYS_WAAS = 0;
        static constexpr int8_t SYS_EGNOS = 1;
        static constexpr int8_t SYS_MSAS = 2;
        static constexpr int8_t SYS_GAGAN = 3;
        static constexpr int8_t SYS_GPS = 16;
        
        uint8_t service;           // SBAS Services available
        static constexpr uint8_t SERVICE_RANGING = 1;
        static constexpr uint8_t SERVICE_CORRECTIONS = 2;
        static constexpr uint8_t SERVICE_INTEGRITY = 4;
        static constexpr uint8_t SERVICE_TESTMODE = 8;
        
        uint8_t cnt;               // Number of SV data following
        std::array<uint8_t, 3> reserved0;      // Reserved
        
        std::vector<NavSBAS_SV> sv;

    };
}
