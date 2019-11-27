#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgDAT {
        // CFG-DAT (0x06 0x06);
        // Set User-defined Datum
        //; 
        // For more information see the description of Geodetic Systems and Frames.
        //; 
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 6;
        
        // Only for GET, these values are not used for write
        uint16_t datumNum;       // Datum Number: 0 = WGS84, 0xFFFF = user-defined
        static constexpr uint16_t DATUM_NUM_WGS84 = 0;
        static constexpr uint16_t DATUM_NUM_USER = 65535;
        
        std::array<uint8_t, 6> datumName;    // ASCII String: WGS84 or USER
        
        double majA;          // Semi-major Axis [m]
                              // accepted range = 6,300,000.0 to 6,500,000.0 meters; 
        double flat;          // 1.0 / Flattening 
                              // accepted range is 0.0 to 500.0;
        
        float dX;            // X Axis shift at the origin [m]
                              // accepted range is +/- 5000.0 meters; 
        float dY;            // Y Axis shift at the origin [m]
                              // accepted range is +/- 5000.0 meters; 
        float dZ;            // Z Axis shift at the origin [m]
                              // accepted range is +/- 5000.0 meters; 
        
        float rotX;          // Rotation about the X Axis [s]
                              // accepted range is +/- 20.0 milli-arc seconds; 
        float rotY;          // Rotation about the Y Axis [s]
                              // accepted range is +/- 20.0 milli-arc seconds; 
        float rotZ;          // Rotation about the Z Axis [s]
                              // accepted range is +/- 20.0 milli-arc seconds;
        
        float scale;         // Scale change [ppm]
                              // accepted range is 0.0 to 50.0 parts per million;
    };
}
