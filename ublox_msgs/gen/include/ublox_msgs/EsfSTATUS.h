#pragma once

#include <array>
#include <vector>
#include "EsfSTATUS_Sens.h"
#include <cstdint>

namespace ublox_msgs {
    struct EsfSTATUS {
        // ESF-STATUS (0x10 0x10);
        // External Sensor Fusion (ESF) status information
        //;
        // Supported on UDR/ADR products
        //;
        
        static constexpr uint8_t CLASS_ID = 16;
        static constexpr uint8_t MESSAGE_ID = 16;
        
        uint32_t iTOW;                   // GPS time of week of the navigation epoch [ms]
        uint8_t version;                 // Message version (2 for this version)
        
        std::array<uint8_t, 7> reserved1;            // Reserved
        
        uint8_t fusionMode;              // Fusion mode:
        static constexpr uint8_t FUSION_MODE_INIT = 0;        // receiver is initializing some unknown values
                                          // required for doing sensor fusion;
        static constexpr uint8_t FUSION_MODE_FUSION = 1;      // GNSS and sensor data are 
                                          // used for navigation solution computation;
        static constexpr uint8_t FUSION_MODE_SUSPENDED = 2;   // sensor fusion is temporarily disabled 
                                          // due to e.g. invalid sensor data or detected; 
                                          // ferry
        static constexpr uint8_t FUSION_MODE_DISABLED = 3;    // sensor fusion is permanently disabled 
                                          // until receiver reset due e.g. to sensor; 
                                          // error
        
        std::array<uint8_t, 2> reserved2;            // Reserved
        
        uint8_t numSens;                 // Number of sensors
        
        
        // Start of repeated block (numSens times);
        std::vector<EsfSTATUS_Sens> sens;
        // End of repeated block
    };
}
