#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct NavATT {
        // NAV-ATT (0x01 0x05);
        // Attitude Solution
        //;
        // This message outputs the attitude solution as roll, pitch and heading angles.
        // Supported on ADR and UDR products.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 5;
        
        uint32_t iTOW;               // GPS time of week of the navigation epoch [ms]
        uint8_t version;             // Message version (0 for this version)
        
        std::array<uint8_t, 3> reserved0;        // Reserved
        
        int32_t roll;                // Vehicle roll. [deg / 1e-5]
        int32_t pitch;               // Vehicle pitch. [deg / 1e-5]
        int32_t heading;             // Vehicle heading. [deg / 1e-5]
        uint32_t accRoll;            // Vehicle roll accuracy (if null, roll angle is not 
                                  // available). [deg / 1e-5];
        uint32_t accPitch;           // Vehicle pitch accuracy (if null, pitch angle is not 
                                  // available). [deg / 1e-5];
        uint32_t accHeading;         // Vehicle heading accuracy [deg / 1e-5]
    };
}
