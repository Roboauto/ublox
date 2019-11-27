#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavVELECEF {
        // NAV-VELECEF (0x01 0x11);
        // Velocity Solution in ECEF
        //;
        // See important comments concerning validity of velocity given in section
        // Navigation Output Filters.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 17;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        
        int32_t ecefVX;            // ECEF X velocity [cm/s]
        int32_t ecefVY;            // ECEF Y velocity [cm/s]
        int32_t ecefVZ;            // ECEF Z velocity [cm/s]
        uint32_t sAcc;             // Speed Accuracy Estimate [cm/s]

    };
}
