#pragma once

#include <vector>
#include "NavDGPS_SV.h"
#include <cstdint>

namespace ublox_msgs {
    struct NavDGPS {
        // NAV-DGPS (0x01 0x31);
        // DGPS Data Used for NAV
        //;
        // This message outputs the Correction data as it has been applied to the current
        // NAV Solution. See also the notes on the RTCM protocol.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 49;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        
        int32_t age;               // Age of newest correction data [ms]
        int16_t baseId;            // DGPS Base Station ID
        int16_t baseHealth;        // DGPS Base Station Health Status
        int8_t numCh;              // Number of channels for which correction data is 
                                // following;
        
        uint8_t status;            // DGPS Correction Type Status
        static constexpr uint8_t DGPS_CORRECTION_NONE = 0;
        static constexpr uint8_t DGPS_CORRECTION_PR_PRR = 1;
        
        uint16_t reserved1;        // Reserved
        
        std::vector<NavDGPS_SV> sv;

    };
}
