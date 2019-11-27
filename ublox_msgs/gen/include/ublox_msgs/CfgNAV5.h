#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgNAV5 {
        // CFG-NAV5 (0x06 0x24);
        // Navigation Engine Settings
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 36;
        
        uint16_t mask;             // Parameters Bitmask. Only the masked
                                // parameters will be applied.;
        static constexpr uint16_t MASK_DYN = 1;                 // Apply dynamic model settings
        static constexpr uint16_t MASK_MIN_EL = 2;              // Apply minimum elevation settings
        static constexpr uint16_t MASK_FIX_MODE = 4;            // Apply fix mode settings
        static constexpr uint16_t MASK_DR_LIM = 8;              // Apply DR limit settings
        static constexpr uint16_t MASK_POS_MASK = 16;           // Apply position mask settings
        static constexpr uint16_t MASK_TIME_MASK = 32;          // Apply time mask settings
        static constexpr uint16_t MASK_STATIC_HOLD_MASK = 64;   // Apply static hold settings
        static constexpr uint16_t MASK_DGPS_MASK = 128;         // Apply DGPS settings, firmware >= 7 only
        static constexpr uint16_t MASK_CNO = 256;               // Apply CNO threshold settings
        static constexpr uint16_t MASK_UTC = 1024;              // Apply UTC settings, protocol >= 16 only
        
        uint8_t dynModel;          // Dynamic Platform model:
        static constexpr uint8_t DYN_MODEL_PORTABLE = 0;        // Portable
        static constexpr uint8_t DYN_MODEL_STATIONARY = 2;      // Stationary
        static constexpr uint8_t DYN_MODEL_PEDESTRIAN = 3;      // Pedestrian
        static constexpr uint8_t DYN_MODEL_AUTOMOTIVE = 4;      // Automotive
        static constexpr uint8_t DYN_MODEL_SEA = 5;             // Sea
        static constexpr uint8_t DYN_MODEL_AIRBORNE_1G = 6;     // Airborne with <1g Acceleration
        static constexpr uint8_t DYN_MODEL_AIRBORNE_2G = 7;     // Airborne with <2g Acceleration
        static constexpr uint8_t DYN_MODEL_AIRBORNE_4G = 8;     // Airborne with <4g Acceleration
        static constexpr uint8_t DYN_MODEL_WRIST_WATCH = 9;     // Wrist watch, protocol >= 18
        
        uint8_t fixMode;           // Position Fixing Mode.
        static constexpr uint8_t FIX_MODE_2D_ONLY = 1;          // 2D only
        static constexpr uint8_t FIX_MODE_3D_ONLY = 2;          // 3D only
        static constexpr uint8_t FIX_MODE_AUTO = 3;             // Auto 2D/3D
        
        int32_t fixedAlt;          // Fixed altitude (mean sea level) for 2D fix mode. 
                                // [m / 0.01];
        uint32_t fixedAltVar;      // Fixed altitude variance for 2D mode. [m^2 / 0.0001]
        int8_t minElev;            // Minimum Elevation for a GNSS satellite to be used in 
                                // NAV [deg];
        uint8_t drLimit;           // Maximum time to perform dead reckoning [s]
                                // (linear extrapolation) in case of GPS signal loss;
        uint16_t pDop;             // Position DOP Mask to use [1 / 0.1]
        uint16_t tDop;             // Time DOP Mask to use [1 / 0.1]
        uint16_t pAcc;             // Position Accuracy Mask [m]
        uint16_t tAcc;             // Time Accuracy Mask [m]
        uint8_t staticHoldThresh;  // Static hold threshold [cm/s]
        uint8_t dgnssTimeOut;      // DGNSS timeout, firmware 7 and newer only [s]
        
        uint8_t cnoThreshNumSvs;   // Number of satellites required to have C/N0 above 
                                // cnoThresh for a fix to be attempted;
        uint8_t cnoThresh;         // C/N0 threshold for deciding whether to attempt a fix
                                // [dBHz];
        std::array<uint8_t, 2> reserved1;      // Reserved
        
        uint16_t staticHoldMaxDist;  // Static hold distance threshold (before quitting 
                                  // static hold) [m];
        uint8_t utcStandard;       // UTC standard to be used:
        static constexpr uint8_t UTC_STANDARD_AUTOMATIC = 0; // receiver selects based on GNSS configuration
        static constexpr uint8_t UTC_STANDARD_GPS = 3;       // UTC as operated by the U.S. Naval Observatory 
                                         // (USNO); derived from GPS time;
        static constexpr uint8_t UTC_STANDARD_GLONASS = 6;   // UTC as operated by the former Soviet Union;
                                         // derived from GLONASS time;
        static constexpr uint8_t UTC_STANDARD_BEIDOU = 7;    // UTC as operated by the National Time Service
                                         // Center, China; derived from BeiDou time;
        std::array<uint8_t, 5> reserved2;      // Reserved
    };
}
