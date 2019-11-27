#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavSOL {
        // NAV-SOL (0x01 0x06);
        // Navigation Solution Information
        //;
        // This message combines Position, velocity and time solution in ECEF, including 
        // accuracy figures;
        // This message has only been retained for backwards compatibility; users are 
        // recommended to use the UBX-NAV-PVT message in preference.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 6;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        int32_t fTOW;              // Fractional Nanoseconds remainder of rounded
                                // ms above, range -500000 .. 500000 [ns];
        int16_t week;              // GPS week (GPS time)
        
        uint8_t gpsFix;            // GPSfix Type, range 0..5
        static constexpr uint8_t GPS_NO_FIX = 0;
        static constexpr uint8_t GPS_DEAD_RECKONING_ONLY = 1;
        static constexpr uint8_t GPS_2D_FIX = 2;
        static constexpr uint8_t GPS_3D_FIX = 3;
        static constexpr uint8_t GPS_GPS_DEAD_RECKONING_COMBINED = 4;
        static constexpr uint8_t GPS_TIME_ONLY_FIX = 5;
        
        uint8_t flags;             // Fix Status Flags
        static constexpr uint8_t FLAGS_GPS_FIX_OK = 1;      // Fix within limits i.e. within DOP & ACC Masks
        static constexpr uint8_t FLAGS_DIFF_SOLN = 2;       // DGPS used
        static constexpr uint8_t FLAGS_WKNSET = 4;          // Week Number valid
        static constexpr uint8_t FLAGS_TOWSET = 8;          // Time of Week valid
        
        int32_t ecefX;             // ECEF X coordinate [cm]
        int32_t ecefY;             // ECEF Y coordinate [cm]
        int32_t ecefZ;             // ECEF Z coordinate [cm]
        uint32_t pAcc;             // 3D Position Accuracy Estimate [cm]
        int32_t ecefVX;            // ECEF X velocity [cm/s]
        int32_t ecefVY;            // ECEF Y velocity [cm/s]
        int32_t ecefVZ;            // ECEF Z velocity [cm/s]
        uint32_t sAcc;             // Speed Accuracy Estimate [cm/s]
        uint16_t pDOP;             // Position DOP [1 / 0.01]
        uint8_t reserved1;         // Reserved
        uint8_t numSV;             // Number of SVs used in Nav Solution
        uint32_t reserved2;        // Reserved

    };
}
