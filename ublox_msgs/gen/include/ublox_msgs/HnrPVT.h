#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct HnrPVT {
        // HNR-PVT (0x28 0x00);
        // High Rate Output of PVT Solution
        //;
        // Note that during a leap second there may be more (or less) than 60 seconds in
        // a minute; see the description of leap seconds for details.;
        //
        // This message provides the position, velocity and time solution with high; 
        // output rate.
        //;
        // Supported on ADR and UDR products.
        //;
        static constexpr uint8_t CLASS_ID = 40;
        static constexpr uint8_t MESSAGE_ID = 0;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        uint16_t year;             // Year (UTC)
        uint8_t month;             // Month, range 1..12 (UTC)
        uint8_t day;               // Day of month, range 1..31 (UTC)
        uint8_t hour;              // Hour of day, range 0..23 (UTC)
        uint8_t min;               // Minute of hour, range 0..59 (UTC)
        uint8_t sec;               // Seconds of minute, range 0..60 (UTC)
        
        uint8_t valid;             // Validity flags
        static constexpr uint8_t VALID_DATE = 1;            // Valid UTC Date
        static constexpr uint8_t VALID_TIME = 2;            // Valid 
        static constexpr uint8_t VALID_FULLY_RESOLVED = 4;  // UTC time of day has been fully resolved 
                                        // (no seconds uncertainty);
        static constexpr uint8_t VALID_MAG = 8;             // Valid Magnetic Declination
        
        int32_t nano;              // fraction of a second [ns], range -1e9 .. 1e9 (UTC)
        
        uint8_t gpsFix;            // GPS fix Type, range 0..5
        static constexpr uint8_t FIX_TYPE_NO_FIX = 0;
        static constexpr uint8_t FIX_TYPE_DEAD_RECKONING_ONLY = 1;
        static constexpr uint8_t FIX_TYPE_2D = 2;                           // Signal from only 3 SVs, 
                                                        // constant altitude assumed;
        static constexpr uint8_t FIX_TYPE_3D = 3;
        static constexpr uint8_t FIX_TYPE_GPS_DEAD_RECKONING_COMBINED = 4;  // GPS + Dead reckoning
        static constexpr uint8_t FIX_TYPE_TIME_ONLY = 5;                    // Time only fix 
        
        uint8_t flags;             // Fix Status Flags
        static constexpr uint8_t FLAGS_GNSS_FIX_OK = 1;          // i.e. within DOP & accuracy masks
        static constexpr uint8_t FLAGS_DIFF_SOLN = 2;            // DGPS used
        static constexpr uint8_t FLAGS_WKN_SET = 4;              // Valid GPS week number
        static constexpr uint8_t FLAGS_TOW_SET = 8;              // Valid GPS time of week (iTOW & fTOW)
        static constexpr uint8_t FLAGS_HEAD_VEH_VALID = 32;      // heading of vehicle is valid
        
        std::array<uint8_t, 2> reserved0;      // Reserved
        
        int32_t lon;               // Longitude [deg / 1e-7]
        int32_t lat;               // Latitude [deg / 1e-7]
        int32_t height;            // Height above Ellipsoid [mm]
        int32_t hMSL;              // Height above mean sea level [mm]
        
        int32_t gSpeed;            // Ground Speed (2-D) [mm/s]
        int32_t speed;             // Speed (3-D) [mm/s]
        
        int32_t headMot;           // Heading of motion (2-D) [deg / 1e-5]
        int32_t headVeh;           // Heading of vehicle (2-D) [deg / 1e-5]
        
        uint32_t hAcc;             // Horizontal Accuracy Estimate [mm]
        uint32_t vAcc;             // Vertical Accuracy Estimate [mm]
        uint32_t sAcc;             // Speed Accuracy Estimate [mm/s]
        uint32_t headAcc;          // Heading Accuracy Estimate (both motion & vehicle) 
                                // [deg / 1e-5];
        
        std::array<uint8_t, 4> reserved1;      // Reserved
    };
}
