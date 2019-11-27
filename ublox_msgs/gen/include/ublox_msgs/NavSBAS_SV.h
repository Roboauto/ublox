#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavSBAS_SV {
        // see message NavSBAS;
        //
        
        uint8_t svid;              // SV Id
        uint8_t flags;             // Flags for this SV
        uint8_t udre;              // Monitoring status
        uint8_t svSys;             // System (WAAS/EGNOS/...), same as SYS
        uint8_t svService;         // Services available, same as SERVICE
        uint8_t reserved1;         // Reserved
        int16_t prc;               // Pseudo Range correction in [cm]
        uint16_t reserved2;        // Reserved
        int16_t ic;                // Ionosphere correction in [cm]

    };
}
