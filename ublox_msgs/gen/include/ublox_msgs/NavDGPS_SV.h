#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavDGPS_SV {
        // see message NavDGPS;
        
        uint8_t svid;              // Satellite ID
        
        uint8_t flags;             // Bitmask / Channel Number and Usage:
        static constexpr uint8_t FLAGS_CHANNEL_MASK = 15;   // Bitmask for channel number, range 0..15
                                        // Channel numbers > 15 marked as 15;
        static constexpr uint8_t FLAGS_DGPS = 16;           // DGPS Used for this SV
        
        uint16_t ageC;             // Age of latest correction data [ms]
        float prc;             // Pseudo Range Correction [m]
        float prrc;            // Pseudo Range Rate Correction [m/s]
        

    };
}
