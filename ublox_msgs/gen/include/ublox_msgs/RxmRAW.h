#pragma once

#include <vector>
#include "RxmRAW_SV.h"
#include <cstdint>

namespace ublox_msgs {
    struct RxmRAW {
        // RXM-RAW (0x02 0x10);
        // Raw Measurement Data
        //;
        // Supported up to ublox 7 firmware. See RxmRAWX for ublox 8
        // This message contains all information needed to be able to generate a RINEX; 
        // observation file.
        // This message outputs pseudorange, doppler and carrier phase measurements for; 
        // GPS satellites once signals have been synchronised. No other GNSS types are 
        // currently supported.;
        // 
        
        static constexpr uint8_t CLASS_ID = 2;
        static constexpr uint8_t MESSAGE_ID = 16;
        
        int32_t rcvTOW;            // Measurement time of week in receiver local time [s]
        int16_t week;              // Measurement week number in receiver local time [weeks]
        
        uint8_t numSV;             // // of satellites following
        uint8_t reserved1;         // Reserved
        
        std::vector<RxmRAW_SV> sv;          // numSV times

    };
}
