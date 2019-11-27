#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct RxmRTCM {
        // RXM-RTCM (0x02 0x32);
        // RTCM input status
        //;
        // Output upon processing of an RTCM input message
        // Supported on:;
        // - u-blox 8 / u-blox M8 from protocol version 20.01 up to version 23.01
        //; 
        
        static constexpr uint8_t CLASS_ID = 2;
        static constexpr uint8_t MESSAGE_ID = 50;
        
        uint8_t version;                 // Message version (0x02 for this version)
        uint8_t flags;                   // RTCM input status flags
        static constexpr uint8_t FLAGS_CRC_FAILED = 1;    // 0 when RTCM message received and passed CRC 
                                      // check, 1 when failed in which case refStation;
                                      // and msgType might be corrupted and misleading
        
        std::array<uint8_t, 2> reserved0;            // Reserved
        
        uint16_t refStation;             // Reference station ID
        uint16_t msgType;                // Message type

    };
}
