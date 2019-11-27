#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct NavPVT {
        // NAV-PVT (0x01 0x07);
        // Navigation Position Velocity Time Solution
        //;
        // Note that during a leap second there may be more (or less) than 60 seconds in
        // a minute; see the description of leap seconds for details.;
        //
        // This message combines Position, velocity and time solution in LLH,; 
        // including accuracy figures
        //;
        // WARNING: For firmware version 7, this message is a different length.
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 7;
        
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
        
        uint32_t tAcc;             // time accuracy estimate [ns] (UTC)
        int32_t nano;              // fraction of a second [ns], range -1e9 .. 1e9 (UTC)
        
        uint8_t fixType;           // GNSS fix Type, range 0..5
        static constexpr uint8_t FIX_TYPE_NO_FIX = 0;
        static constexpr uint8_t FIX_TYPE_DEAD_RECKONING_ONLY = 1;
        static constexpr uint8_t FIX_TYPE_2D = 2;                           // Signal from only 3 SVs, 
                                                        // constant altitude assumed;
        static constexpr uint8_t FIX_TYPE_3D = 3;
        static constexpr uint8_t FIX_TYPE_GNSS_DEAD_RECKONING_COMBINED = 4; // GNSS + Dead reckoning
        static constexpr uint8_t FIX_TYPE_TIME_ONLY = 5;                    // Time only fix (High precision 
                                                        // devices);
        
        uint8_t flags;             // Fix Status Flags
        static constexpr uint8_t FLAGS_GNSS_FIX_OK = 1;          // i.e. within DOP & accuracy masks
        static constexpr uint8_t FLAGS_DIFF_SOLN = 2;            // DGDGPS used
        static constexpr uint8_t FLAGS_PSM_MASK = 28;            // Power Save Mode
        static constexpr uint8_t PSM_OFF = 0;                       // PSM is off
        static constexpr uint8_t PSM_ENABLED = 4;                   // Enabled (state before acquisition)
        static constexpr uint8_t PSM_ACQUIRED = 8;                  // Acquisition
        static constexpr uint8_t PSM_TRACKING = 12;                 // Tracking
        static constexpr uint8_t PSM_POWER_OPTIMIZED_TRACKING = 16; // Power Optimized Tracking
        static constexpr uint8_t PSM_INACTIVE = 20;                 // Inactive
        static constexpr uint8_t FLAGS_HEAD_VEH_VALID = 32;         // heading of vehicle is valid
        static constexpr uint8_t FLAGS_CARRIER_PHASE_MASK = 192; // Carrier Phase Range Solution Status     
        static constexpr uint8_t CARRIER_PHASE_NO_SOLUTION = 0;     // no carrier phase range solution
        static constexpr uint8_t CARRIER_PHASE_FLOAT = 64;          // carrier phase float solution (no fixed 
                                                // integer measurements have been used to; 
                                                // calculate the solution)
        static constexpr uint8_t CARRIER_PHASE_FIXED = 128;         // fixed solution (>=1 fixed integer 
                                                // carrier phase range measurements have; 
                                                // been used to calculate  the solution)
        
        uint8_t flags2;            // Additional Flags
        static constexpr uint8_t FLAGS2_CONFIRMED_AVAILABLE = 32;   // information about UTC Date and Time of 
                                                // Day validity confirmation is available;
        static constexpr uint8_t FLAGS2_CONFIRMED_DATE = 64;        // UTC Date validity could be confirmed
        static constexpr uint8_t FLAGS2_CONFIRMED_TIME = 128;       // UTC Time of Day could be confirmed
        
        uint8_t numSV;             // Number of SVs used in Nav Solution
        int32_t lon;               // Longitude [deg / 1e-7]
        int32_t lat;               // Latitude [deg / 1e-7]
        int32_t height;            // Height above Ellipsoid [mm]
        int32_t hMSL;              // Height above mean sea level [mm]
        uint32_t hAcc;             // Horizontal Accuracy Estimate [mm]
        uint32_t vAcc;             // Vertical Accuracy Estimate [mm]
        
        int32_t velN;              // NED north velocity [mm/s]
        int32_t velE;              // NED east velocity [mm/s]
        int32_t velD;              // NED down velocity [mm/s]
        int32_t gSpeed;            // Ground Speed (2-D) [mm/s]
        int32_t heading;           // Heading of motion 2-D [deg / 1e-5]
        uint32_t sAcc;             // Speed Accuracy Estimate [mm/s]
        uint32_t headAcc;          // Heading Accuracy Estimate (both motion & vehicle) 
                                // [deg / 1e-5];
        
        uint16_t pDOP;             // Position DOP [1 / 0.01]
        std::array<uint8_t, 6> reserved1;      // Reserved
        
        int32_t headVeh;           // Heading of vehicle (2-D) [deg / 1e-5]
        int16_t magDec;            // Magnetic declination [deg / 1e-2]
        uint16_t magAcc;           // Magnetic declination accuracy [deg / 1e-2]

    };
}
