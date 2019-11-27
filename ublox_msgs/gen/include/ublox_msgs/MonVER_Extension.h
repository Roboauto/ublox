#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct MonVER_Extension {
        // see MonVER message;
        //
        
        std::array<char, 30> field;
    };
}
