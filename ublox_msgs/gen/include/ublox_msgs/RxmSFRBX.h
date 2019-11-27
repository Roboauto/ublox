#pragma once

#include <vector>
#include <cstdint>

namespace ublox_msgs {
    struct RxmSFRBX {
        // RXM-SFRB (0x02 0x13);
        // Subframe Buffer
        //;
        // This message reports a complete subframe of broadcast navigation data decoded 
        // from a single signal. The number of data words reported in each message;
        // depends on the nature of the signal. See the section on Broadcast Navigation
        // Data for further details.;
        //
        
        static constexpr uint8_t CLASS_ID = 2;
        static constexpr uint8_t MESSAGE_ID = 19;
        
        uint8_t gnssId;            // GNSS identifier (see Cfg GNSS for constants)
        
        uint8_t svId;              // Satellite identifier within corresponding GNSS system
        uint8_t reserved0;         // Reserved
        uint8_t freqId;            // Only used for GLONASS: This is the frequency
                                // slot + 7 (range from 0 to 13);
        uint8_t numWords;          // The number of data words contained in this message (up
                                // to 10, for currently supported signals);
        uint8_t chn;               // The tracking channel number the message was received
                                // on;
        uint8_t version;           // Message version, (0x02 for this version)
        uint8_t reserved1;         // Reserved
        
        // Start of repeated block (numWords times);
        std::vector<uint32_t> dwrd;           // The data words
        // End of repeated block;
    };
}
