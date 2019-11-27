#pragma once

#include <vector>
#include "CfgINF_Block.h"
#include <cstdint>

namespace ublox_msgs {
    struct CfgINF {
        // CFG-INF  (0x06 0x02);
        // Information message configuration
        //;
        // The value of infMsgMask[x] below are that each bit represents one of the INF 
        // class messages (Bit 0 for ERROR, Bit 1 for WARNING and so on.). For a complete; 
        // list, see the Message Class INF. Several configurations can be concatenated to 
        // one input message.;
        // In this case the payload length can be a multiple of the normal length. Output 
        // messages from the module contain only one configuration unit. Note that I/O; 
        // Ports 1 and 2 correspond to serial ports 1 and 2. I/O port 0 is DDC. I/O port 
        // 3 is USB. I/O port 4 is SPI. I/O port 5 is reserved for future use;
        //
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 2;
        
        // start of repeated block
        std::vector<CfgINF_Block> blocks;
        // end of repeated block

    };
}
