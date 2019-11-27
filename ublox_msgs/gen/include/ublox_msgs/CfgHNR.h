#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgHNR {
        // CFG-HNR (0x06 0x5C);
        // High Navigation Rate Settings
        //;
        // The u-blox receivers support high rates of navigation update up to 30 Hz. 
        // The navigation solution output (NAV-HNR) will not be aligned to the top of a;
        // second.
        // The update rate has a direct influence on the power consumption. The more;
        // fixes that are required, the more CPU power and communication resources are 
        // required.;
        // For most applications a 1 Hz update rate would be sufficient.
        //;
        // (only with ADR or UDR products)
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 92;
        
        uint8_t highNavRate;     // Rate of navigation solution output [Hz]
        std::array<uint8_t, 3> reserved0;    // Reserved
    };
}
