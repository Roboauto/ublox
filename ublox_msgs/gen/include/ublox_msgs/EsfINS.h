#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct EsfINS {
        // ESF-INS (0x10 0x15);
        // Vehicle dynamics information
        //; 
        // This message outputs information about vehicle dynamics computed by the 
        // Inertial Navigation System (INS) during ESF-based navigation.;
        // For ADR products, the output dynamics information (angular rates and 
        // accelerations) is expressed with respect to the vehicle-frame.;
        // For UDR products, the output dynamics information (angular rates and 
        // accelerations) is expressed with respect to the body-frame.;
        //
        
        static constexpr uint8_t CLASS_ID = 16;
        static constexpr uint8_t MESSAGE_ID = 21;
        
        uint32_t bitfield0;      // Bitfield (see graphic below)
        static constexpr uint32_t BITFIELD0_VERSION = 255;            // Message version (1 for this version).
        static constexpr uint32_t BITFIELD0_X_ANG_RATE_VALID = 256;   // Compensated x-axis angular rate data 
                                                  // validity flag;
        static constexpr uint32_t BITFIELD0_Y_ANG_RATE_VALID = 512;   // Compensated y-axis angular rate data 
                                                  // validity flag;
        static constexpr uint32_t BITFIELD0_Z_ANG_RATE_VALID = 1024;  // Compensated z-axis angular rate data 
                                                  // validity flag;
        static constexpr uint32_t BITFIELD0_X_ACCEL_VALID = 2048;     // Compensated x-axis acceleration data 
                                                  // validity flag;
        static constexpr uint32_t BITFIELD0_Y_ACCEL_VALID = 4096;     // Compensated y-axis acceleration data 
                                                  // validity flag;
        static constexpr uint32_t BITFIELD0_Z_ACCEL_VALID = 8192;     // Compensated z-axis acceleration data 
                                                  // validity flag;
        
        std::array<uint8_t, 4> reserved1;    // Reserved
        
        uint32_t iTOW;           // GPS time of week of the navigation epoch [ms]
        int32_t xAngRate;        // Compensated x-axis angular rate [deg/s / 1e-3]
        int32_t yAngRate;        // Compensated y-axis angular rate [deg/s / 1e-3]
        int32_t zAngRate;        // Compensated z-axis angular rate [deg/s / 1e-3]
        int32_t xAccel;          // Compensated x-axis acceleration (gravity-free) [mg]
        int32_t yAccel;          // Compensated y-axis acceleration (gravity-free) [mg]
        int32_t zAccel;          // Compensated z-axis acceleration (gravity-free) [mg]
    };
}
