#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavSTATUS {
        // NAV-STATUS (0x01 0x03);
        // Receiver Navigation Status
        //;
        // See important comments concerning validity of position and velocity given in
        // section Navigation Output Filters.;
        //
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 3;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        
        uint8_t gpsFix;            // GPSfix Type, this value does not qualify a fix as
                                // valid and within the limits. See note on flag gpsFixOk;
                                // below
        static constexpr uint8_t GPS_NO_FIX = 0;
        static constexpr uint8_t GPS_DEAD_RECKONING_ONLY = 1;
        static constexpr uint8_t GPS_2D_FIX = 2;
        static constexpr uint8_t GPS_3D_FIX = 3;
        static constexpr uint8_t GPS_GPS_DEAD_RECKONING_COMBINED = 4;
        static constexpr uint8_t GPS_TIME_ONLY_FIX = 5;
        
        uint8_t flags;             // Navigation Status Flags
        static constexpr uint8_t FLAGS_GPS_FIX_OK = 1;      // position & velocity valid & within DOP & ACC 
                                        // Masks;
        static constexpr uint8_t FLAGS_DIFF_SOLN = 2;       // Differential corrections were applied
        static constexpr uint8_t FLAGS_WKNSET = 4;          // Week Number valid
        static constexpr uint8_t FLAGS_TOWSET = 8;          // Time of Week valid
        
        uint8_t fixStat;           // Fix Status Information
        static constexpr uint8_t FIX_STAT_DIFF_CORR_MASK = 1;       // 1 = differential corrections available
        // map matching status:;
        static constexpr uint8_t FIX_STAT_MAP_MATCHING_MASK = 192;
        static constexpr uint8_t MAP_MATCHING_NONE = 0;      // none
        static constexpr uint8_t MAP_MATCHING_VALID = 64;    // valid but not used, i.e. map matching data 
                                         // was received, but was too old;
        static constexpr uint8_t MAP_MATCHING_USED = 128;    // valid and used, map matching data was applied
        static constexpr uint8_t MAP_MATCHING_DR = 192;      // valid and used, map matching data was 
                                         // applied. In case of sensor unavailability map;
                                         // matching data enables dead reckoning. 
                                         // This requires map matched latitude/longitude; 
                                         // or heading data.
        
        uint8_t flags2;            // further information about navigation output
        // power safe mode state (Only for FW version >= 7.01; undefined otherwise);
        static constexpr uint8_t FLAGS2_PSM_STATE_MASK = 3;
        static constexpr uint8_t PSM_STATE_ACQUISITION = 0;                // ACQUISITION 
                                                       // [or when psm disabled];
        static constexpr uint8_t PSM_STATE_TRACKING = 1;                   // TRACKING
        static constexpr uint8_t PSM_STATE_POWER_OPTIMIZED_TRACKING = 2;   // POWER OPTIMIZED TRACKING
        static constexpr uint8_t PSM_STATE_INACTIVE = 3;                   // INACTIVE
        // Note that the spoofing state value only reflects the detector state for the; 
        // current navigation epoch. As spoofing can be detected most easily at the 
        // transition from real signal to spoofing signal, this is also where the; 
        // detector is triggered the most. I.e. a value of 1 - No spoofing indicated does
        // not mean that the receiver is not spoofed, it; //simply states that the detector
        // was not triggered in this epoch.;
        static constexpr uint8_t FLAGS2_SPOOF_DET_STATE_MASK = 24; 
        static constexpr uint8_t SPOOF_DET_STATE_UNKNOWN = 0;    // Unknown or deactivated
        static constexpr uint8_t SPOOF_DET_STATE_NONE = 8;       // No spoofing indicated
        static constexpr uint8_t SPOOF_DET_STATE_SPOOFING = 16;  // Spoofing indicated
        static constexpr uint8_t SPOOF_DET_STATE_MULTIPLE = 24;  // Multiple spoofing indication
        
        uint32_t ttff;             // Time to first fix (millisecond time tag) [ms]
        uint32_t msss;             // Milliseconds since Startup / Reset [ms]

    };
}
