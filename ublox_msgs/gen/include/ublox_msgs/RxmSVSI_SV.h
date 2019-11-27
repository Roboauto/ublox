#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct RxmSVSI_SV {
        // see message RxmSVSI;
        //
        
        uint8_t svid;            // Satellite ID
        
        uint8_t svFlag;          // Information Flags
        static constexpr uint8_t FLAG_URA_MASK = 15;      // Figure of Merit (URA) range 0..15
        static constexpr uint8_t FLAG_HEALTHY = 16;       // SV healthy flag
        static constexpr uint8_t FLAG_EPH_VAL = 32;       // Ephemeris valid
        static constexpr uint8_t FLAG_ALM_VAL = 64;       // Almanac valid
        static constexpr uint8_t FLAG_NOT_AVAIL = 128;    // SV not available
        
        int16_t azim;            // Azimuth
        int8_t elev;             // Elevation
        
        uint8_t age;             // Age of Almanac and Ephemeris
        static constexpr uint8_t AGE_ALM_MASK = 15;       // Age of ALM in days offset by 4
                                      // i.e. the reference time may be in the future:;
                                      // ageOfAlm = (age & 0x0f) - 4
        static constexpr uint8_t AGE_EPH_MASK = 240;      // Age of EPH in hours offset by 4.
                                      // i.e. the reference time may be in the future:;
                                      // ageOfEph = ((age & 0xf0) >> 4) - 4

    };
}
