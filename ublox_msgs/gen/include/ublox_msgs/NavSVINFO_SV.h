#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavSVINFO_SV {
        // see message NavSVINFO;
        //
        
        uint8_t chn;             // Channel number, 255 for SVs not assigned to a channel
        uint8_t svid;            // Satellite ID
        
        uint8_t flags;           // Bitmask
        static constexpr uint8_t FLAGS_SV_USED = 1;                     // SV is used for navigation
        static constexpr uint8_t FLAGS_DIFF_CORR = 2;                   // Differential correction data 
                                                    // is available for this SV;
        static constexpr uint8_t FLAGS_ORBIT_AVAIL = 4;                 // Orbit information is available for 
                                                    // this SV (Ephemeris or Almanach);
        static constexpr uint8_t FLAGS_ORBIT_EPH = 8;                   // Orbit information is Ephemeris
        static constexpr uint8_t FLAGS_UNHEALTHY = 16;                  // SV is unhealthy / shall not be 
                                                    // used;
        static constexpr uint8_t FLAGS_ORBIT_ALM = 32;                  // Orbit information is Almanac Plus
        static constexpr uint8_t FLAGS_ORBIT_AOP = 64;                  // Orbit information is AssistNow 
                                                    // Autonomous;
        static constexpr uint8_t FLAGS_SMOOTHED = 128;                  // Carrier smoothed pseudorange used
        
        uint8_t quality;         // Bitfield
        // qualityInd: Signal Quality indicator (range 0..7). The following list shows; 
        // the meaning of the different QI values:
        // Note: Since IMES signals are not time synchronized, a channel tracking an IMES;
        // signal can never reach a quality indicator value of higher than 3.
        static constexpr uint8_t QUALITY_IDLE = 0;                      // This channel is idle
        static constexpr uint8_t QUALITY_SEARCHING = 1;                 // Channel is searching
        static constexpr uint8_t QUALITY_ACQUIRED = 2;                   // Signal acquired
        static constexpr uint8_t QUALITY_DETECTED = 3;                  // Signal detected but unusable
        static constexpr uint8_t QUALITY_CODE_LOCK = 4;                 // Code Lock on Signal
        static constexpr uint8_t QUALITY_CODE_AND_CARRIER_LOCKED1 = 5;  // Code and Carrier locked 
                                                    // and time synchronized;
        static constexpr uint8_t QUALITY_CODE_AND_CARRIER_LOCKED2 = 6;  // Code and Carrier locked 
                                                    // and time synchronized;
        static constexpr uint8_t QUALITY_CODE_AND_CARRIER_LOCKED3 = 7;  // Code and Carrier locked 
                                                    // and time synchronized;
        
        uint8_t cno;             // Carrier to Noise Ratio (Signal Strength) [dBHz]
        int8_t elev;             // Elevation in integer degrees [deg]
        int16_t azim;            // Azimuth in integer degrees [deg]
        int32_t prRes;           // Pseudo range residual in centimetres [cm]

    };
}
