#pragma once

#include <array>
#include <vector>
#include "MonVER_Extension.h"
#include <cstdint>

namespace ublox_msgs {
    struct MonVER {
        // MON-VER (0x0A 0x04);
        //
        // Receiver/Software Version;
        // Returned when the version is polled.
        
        static constexpr uint8_t CLASS_ID = 10;
        static constexpr uint8_t MESSAGE_ID = 4;
        
        std::array<char, 30> swVersion{};    // Zero-terminated software version string.
        std::array<char, 10> hwVersion{};    // Zero-terminated hardware version string.
        
        // Start of repeated block (N times);
        std::vector<MonVER_Extension> extension{};
        // End of repeated block

    };
}
