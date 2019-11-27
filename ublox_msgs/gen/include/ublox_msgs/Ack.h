#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct Ack {
        // ACK (0x05);
        // Message Acknowledged / Not-Acknowledged
        //;
        // Output upon processing of an input message
        //;
        
        static constexpr uint8_t CLASS_ID = 5;
        static constexpr uint8_t NACK_MESSAGE_ID = 0;
        static constexpr uint8_t ACK_MESSAGE_ID = 1;
        
        uint8_t clsID;   // Class ID of the (Not-)Acknowledged Message
        uint8_t msgID;   // Message ID of the (Not-)Acknowledged Message
    };
}
