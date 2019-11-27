#pragma once

#include <vector>
#include "NavSVINFO_SV.h"
#include <cstdint>

namespace ublox_msgs {
    struct NavSVINFO {
        // NAV-SVINFO (0x01 0x30);
        // Space Vehicle Information
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 48;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        
        uint8_t numCh;             // Number of channels
        
        uint8_t globalFlags;       // Bitmask
        // Chip Hardware generation flags;
        static constexpr uint8_t CHIPGEN_ANTARIS = 0;   // Antaris, Antaris 4
        static constexpr uint8_t CHIPGEN_UBLOX5 = 1;    // u-blox 5
        static constexpr uint8_t CHIPGEN_UBLOX6 = 2;    // u-blox 6
        static constexpr uint8_t CHIPGEN_UBLOX7 = 3;    // u-blox 7
        static constexpr uint8_t CHIPGEN_UBLOX8 = 4;    // u-blox 8 / u-blox M8
        
        uint16_t reserved2;        // Reserved
        
        std::vector<NavSVINFO_SV> sv;

    };
}
