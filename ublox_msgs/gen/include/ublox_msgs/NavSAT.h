#pragma once

#include <array>
#include <vector>
#include "NavSAT_SV.h"
#include <cstdint>

namespace ublox_msgs {
    struct NavSAT {
        // NAV-SAT (0x01 0x35);
        // Satellite Information
        //;
        // This message displays information about SVs which are either known to be 
        // visible or currently tracked by the receiver.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 53;
        
        uint32_t iTOW;                // GPS time of week of the navigation epoch. [ms]
        uint8_t version;              // Message version (1 for this version)
        uint8_t numSvs;               // Number of satellites
        std::array<uint8_t, 2> reserved0;         // Reserved 
        
        // start of repeated block (numSvs times);
        std::vector<NavSAT_SV>  sv;
        // end of repeated block
    };
}
