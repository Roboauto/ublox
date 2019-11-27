#pragma once

#include <vector>
#include <cstdint>

namespace ublox_msgs {
    struct Inf {
        // UBX-INF (0x04, 0x00...0x04);
        // ASCII output
        //;
        // This message has a variable length payload, representing an ASCII string.
        //;
        
        static constexpr uint8_t CLASS_ID = 4;
        
        std::vector<char> str;
    };
}
