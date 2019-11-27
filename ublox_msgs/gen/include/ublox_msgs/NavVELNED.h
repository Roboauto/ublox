#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavVELNED {
        // NAV-VELNED (0x01 0x12);
        // Velocity Solution in NED
        //;
        // See important comments concerning validity of velocity given in section
        // Navigation Output Filters.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 18;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        
        int32_t velN;              // NED north velocity [cm/s]
        int32_t velE;              // NED east velocity [cm/s]
        int32_t velD;              // NED down velocity [cm/s]
        uint32_t speed;            // Speed (3-D) [cm/s]
        uint32_t gSpeed;           // Ground Speed (2-D) [cm/s]
        int32_t heading;           // Heading of motion 2-D [deg / 1e-5]
        uint32_t sAcc;             // Speed Accuracy Estimate [cm/s]
        uint32_t cAcc;             // Course / Heading Accuracy Estimate [deg / 1e-5]

    };
}
