#pragma once

#include <array>
#include <vector>
#include "EsfRAW_Block.h"
#include <cstdint>

namespace ublox_msgs {
    struct EsfRAW {
        // ESF-RAW (0x10 0x03);
        // Raw sensor measurements
        //;
        // The message contains measurements from the active inertial sensors connected
        // to the GNSS chip. Possible data types for the data field are accelerometer,;
        // gyroscope and temperature readings as described in the ESF Measurement Data
        // section. Note that the rate selected in CFG-MSG is not respected. If a;
        // positive rate is selected then all raw measurements will be output. 
        //;
        // Supported on ADR/UDR products.
        //;
        
        static constexpr uint8_t CLASS_ID = 16;
        static constexpr uint8_t MESSAGE_ID = 3;
        
        std::array<uint8_t, 4> reserved0; // Reserved
        
        std::vector<EsfRAW_Block> blocks;
    };
}
