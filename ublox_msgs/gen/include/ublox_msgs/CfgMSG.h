#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgMSG {
        // CFG-MSG (0x06 0x01);
        // Message Rate(s)
        //; 
        // Set message rate for the current port
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 1;
        
        uint8_t msgClass;            // Message Class
        uint8_t msgID;               // Message Identifier
        uint8_t rate;                // Send rate on current port 
                                  // [number of navigation solutions];

    };
}
