#pragma once

#include <vector>
#include "RxmSVSI_SV.h"
#include <cstdint>

namespace ublox_msgs {
    struct RxmSVSI {
        // RXM-SVSI (0x02 0x20);
        // SV Status Info
        //;
        // Status of the receiver manager knowledge about GPS Orbit Validity
        //;
        // This message has only been retained for backwards compatibility; users are
        // recommended to use the UBX-NAV-ORB message in preference.;
        
        static constexpr uint8_t CLASS_ID = 2;
        static constexpr uint8_t MESSAGE_ID = 32;
        
        int32_t iTOW;              // GPS time of week of the navigation epoch [ms]
        int16_t week;              // GPS week number of the navigation epoch [weeks]
        
        uint8_t numVis;            // Number of visible satellites
        uint8_t numSV;             // Number of per-SV data blocks following
        
        std::vector<RxmSVSI_SV> sv;

    };
}
