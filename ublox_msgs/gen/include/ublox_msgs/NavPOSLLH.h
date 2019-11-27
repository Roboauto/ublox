#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavPOSLLH {
        // NAV-POSLLH (0x01 0x02);
        // Geodetic Position Solution
        //;
        // See important comments concerning validity of position given in section
        // Navigation Output Filters.;
        // This message outputs the Geodetic position in the currently selected 
        // Ellipsoid. The default is the WGS84 Ellipsoid, but can be changed with the;
        // message CFG-DAT.
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 2;
        
        uint32_t iTOW;             // GPS Millisecond Time of Week [ms]
        
        int32_t lon;               // Longitude [deg / 1e-7]
        int32_t lat;               // Latitude [deg / 1e-7]
        int32_t height;            // Height above Ellipsoid [mm]
        int32_t hMSL;              // Height above mean sea level [mm]
        uint32_t hAcc;             // Horizontal Accuracy Estimate [mm]
        uint32_t vAcc;             // Vertical Accuracy Estimate [mm]

    };
}
