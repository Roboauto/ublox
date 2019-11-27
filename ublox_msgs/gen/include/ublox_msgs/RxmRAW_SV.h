#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct RxmRAW_SV {
        // see message RxmRAW;
        //
        
        double cpMes;             // Carrier phase measurement [L1 cycles]
        double prMes;             // Pseudorange measurement [m]
        float doMes;             // Doppler measurement [Hz]
        
        uint8_t sv;                  // Space Vehicle Number
        int8_t mesQI;                // Nav Measurements Quality Indicator
                                  //  >=4 : PR+DO OK;
                                  //  >=5 : PR+DO+CP OK
                                  //  <6 : likely loss of carrier lock in previous; 
                                  //       interval
        int8_t cno;                  // Signal strength C/No. [dbHz]
        uint8_t lli;                 // Loss of lock indicator (RINEX definition)

    };
}
