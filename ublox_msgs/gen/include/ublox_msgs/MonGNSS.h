#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct MonGNSS {
        // MON-GNSS (0x0A 0x28);
        // Information message major GNSS selection
        //;
        // This message reports major GNSS selection. Augmentation systems are not
        // reported.;
        // 
        
        static constexpr uint8_t CLASS_ID = 10;
        static constexpr uint8_t MESSAGE_ID = 40;
        
        uint8_t version;         // Message version (0x01 for this version)
        
        static constexpr uint8_t BIT_MASK_GPS = 1;
        static constexpr uint8_t BIT_MASK_GLONASS = 2;
        static constexpr uint8_t BIT_MASK_BEIDOU = 4;
        static constexpr uint8_t BIT_MASK_GALILEO = 8;
        
        uint8_t supported;       // The major GNSS that can be supported by this receiver
        uint8_t defaultGnss;     // Default major GNSS selection. If the default major GNSS 
                              // selection is currently configured in the efuse for this; 
                              // receiver, it takes precedence over the default major 
                              // GNSS selection configured in the executing firmware of; 
                              // this receiver.
                              // see bit mask constants;
        uint8_t enabled;         // Current major GNSS selection enabled for this receiver
                              // see bit mask constants;
        
        uint8_t simultaneous;    // Maximum number of concurrent major GNSS that can be 
                              // supported by this receiver;
        
        std::array<uint8_t, 3> reserved1;    // Reserved

    };
}
