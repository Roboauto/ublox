#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct NavSVIN {
        // NAV-SVIN (0x01 0x3B);
        // Survey-in data
        //; 
        // This message contains information about survey-in parameters.
        // Supported on:;
        //  - u-blox 8 / u-blox M8 with protocol version 20 (only with High Precision
        //    GNSS products);
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 59;
        
        uint8_t version;           // Message version (0x00 for this version)
        std::array<uint8_t, 3> reserved0;      // Reserved
        
        uint32_t iTOW;             // GPS time of week of the navigation epoch [ms]
        
        uint32_t dur;              // Passed survey-in observation time [s]
        
        int32_t meanX;             // Current survey-in mean position ECEF X coordinate [cm]
        int32_t meanY;             // Current survey-in mean position ECEF Y coordinate [cm]
        int32_t meanZ;             // Current survey-in mean position ECEF Z coordinate [cm]
        
        int8_t meanXHP;            // Current high-precision survey-in mean position
                                // ECEF X coordinate. 0.1_mm; 
                                // Must be in the range -99..+99.
                                // The current survey-in mean position ECEF X;
                                // coordinate, in units of cm, is given by
                                // meanX + (0.01 * meanXHP);
        int8_t meanYHP;            // Current high-precision survey-in mean position
                                // ECEF Y coordinate. [0.1 mm]; 
                                // Must be in the range -99..+99.
                                // The current survey-in mean position ECEF Y;
                                // coordinate, in units of cm, is given by
                                // meanY + (0.01 * meanYHP);
        int8_t meanZHP;            // Current high-precision survey-in mean position
                                // ECEF Z coordinate. [0.1 mm]; 
                                // Must be in the range -99..+99.
                                // The current survey-in mean position ECEF Z;
                                // coordinate, in units of cm, is given by
                                // meanZ + (0.01 * meanZHP);
        
        uint8_t reserved1;         // Reserved
        
        uint32_t meanAcc;          // Current survey-in mean position accuracy [0.1 mm]
        uint32_t obs;              // Number of position observations used during survey-in
        uint8_t valid;             // Survey-in position validity flag, 1 = valid
                                // otherwise 0;
        uint8_t active;            // Survey-in in progress flag, 1 = in-progress
                                // otherwise 0;
        
        std::array<uint8_t, 2> reserved3;      // Reserved
    };
}
