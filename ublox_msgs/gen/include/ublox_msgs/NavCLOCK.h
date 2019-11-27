#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavCLOCK {
        // NAV-CLOCK (0x01 0x22);
        // Clock Solution
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 34;
        
        uint32_t iTOW;             // GPS Millisecond Time of week [ms]
        
        int32_t clkB;              // Clock bias in nanoseconds [ns]
        int32_t clkD;              // Clock drift in nanoseconds per second [ns/s]
        uint32_t tAcc;             // Time Accuracy Estimate [ns]
        uint32_t fAcc;             // Frequency Accuracy Estimate [ps/s]

    };
}
