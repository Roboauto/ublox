#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgDGNSS {
        // CFG-DGNSS (0x06 0x70);
        // DGNSS configuration
        //;
        // This message allows the user to configure the DGNSS configuration of the 
        // receiver.;
        // Supported on:
        //  - u-blox 8 / u-blox M8 from protocol version 20.01 up to version 23.01 (only;
        //    with High Precision GNSS products)
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 112;
        
        uint8_t dgnssMode;                 // Specifies differential mode:
        static constexpr uint8_t DGNSS_MODE_RTK_FLOAT = 2;    // RTK float: No attempts are made to fix
                                          // ambiguities.;
        static constexpr uint8_t DGNSS_MODE_RTK_FIXED = 3;    // RTK fixed: Ambiguities are fixed whenever
                                          // possible.;
        std::array<uint8_t, 3> reserved0;              // Reserved
    };
}
