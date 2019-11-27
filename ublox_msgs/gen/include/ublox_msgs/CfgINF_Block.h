#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgINF_Block {
        // See CfgINF message;
        //
        
        uint8_t protocolID;          // Protocol Identifier, identifying for which
                                  // protocol the configuration is set/get. The;
                                  // following are valid Protocol Identifiers:
                                  // 0: UBX Protocol;
                                  // 1: NMEA Protocol
                                  // 2-255: Reserved;
        static constexpr uint8_t PROTOCOL_ID_UBX = 0;
        static constexpr uint8_t PROTOCOL_ID_NMEA = 1;
        
        std::array<uint8_t, 3> reserved1;        // Reserved
        
        std::array<uint8_t, 6> infMsgMask;       // A bit mask, saying which information messages
                                  // are enabled on each I/O port;
        static constexpr uint8_t INF_MSG_ERROR = 1;              // enable ERROR
        static constexpr uint8_t INF_MSG_WARNING = 2;            // enable WARNING
        static constexpr uint8_t INF_MSG_NOTICE = 4;             // enable NOTICE
        static constexpr uint8_t INF_MSG_TEST = 8;               // enable TEST
        static constexpr uint8_t INF_MSG_DEBUG = 16;             // enable DEBUG
    };
}
