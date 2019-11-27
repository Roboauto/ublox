#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavTIMEGPS {
        // NAV-TIMEGPS (0x01 0x20);
        // GPS Time Solution
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 32;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        int32_t fTOW;              // Fractional Nanoseconds remainder of rounded
                                // ms above, range -500000 .. 500000 [ns];
        int16_t week;              // GPS week (GPS time)
        
        int8_t leapS;              // Leap Seconds (GPS-UTC) [s]
        
        uint8_t valid;             // Validity Flags
        static constexpr uint8_t VALID_TOW = 1;        // Valid Time of Week
        static constexpr uint8_t VALID_WEEK = 2;       // Valid Week Number
        static constexpr uint8_t VALID_LEAP_S = 4;     // Valid Leap Seconds
        
        uint32_t tAcc;             // Time Accuracy Estimate [ns]

    };
}
