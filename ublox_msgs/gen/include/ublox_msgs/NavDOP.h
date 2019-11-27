#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavDOP {
        // NAV-DOP (0x01 0x04);
        // Dilution of precision
        //;
        // - DOP values are dimensionless.
        // - All DOP values are scaled by a factor of 100. If the unit transmits a value; 
        //   of e.g. 156, the DOP value is 1.56.
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 4;
        
        uint32_t iTOW;             // GPS Millisecond Time of Week [ms]
        
        uint16_t gDOP;             // Geometric DOP [1 / 0.01]
        uint16_t pDOP;             // Position DOP  [1 / 0.01]
        uint16_t tDOP;             // Time DOP [1 / 0.01]
        uint16_t vDOP;             // Vertical DOP [1 / 0.01]
        uint16_t hDOP;             // Horizontal DOP [1 / 0.01]
        uint16_t nDOP;             // Northing DOP [1 / 0.01]
        uint16_t eDOP;             // Easting DOP [1 / 0.01]

    };
}
