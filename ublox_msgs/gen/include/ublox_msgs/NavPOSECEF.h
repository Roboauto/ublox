#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavPOSECEF {
        // NAV-POSECEF (0x01 0x01);
        // Position Solution in ECEF
        //;
        // See important comments concerning validity of position given in section
        // Navigation Output Filters.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 1;
        
        uint32_t iTOW;             // GPS Millisecond Time of Week [ms]
        
        int32_t ecefX;             // ECEF X coordinate [cm]
        int32_t ecefY;             // ECEF Y coordinate [cm]
        int32_t ecefZ;             // ECEF Z coordinate [cm]
        uint32_t pAcc;             // Position Accuracy Estimate [cm]

    };
}
