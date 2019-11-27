#pragma once

#include <array>
#include <vector>
#include "RxmRAWX_Meas.h"
#include <cstdint>

namespace ublox_msgs {
    struct RxmRAWX {
        // RXM-RAWX (0x02 0x15);
        // Multi-GNSS Raw Measurement Data
        //;
        // This message contains the information needed to be able to generate a RINEX 3
        // multi-GNSS observation file.;
        // This message contains pseudorange, Doppler, carrier phase, phase lock and
        // signal quality information for GNSS satellites once signals have been;
        // synchronized. This message supports all active GNSS.
        //; 
        
        static constexpr uint8_t CLASS_ID = 2;
        static constexpr uint8_t MESSAGE_ID = 21;
        
        double rcvTOW;          // Measurement time of week in receiver local time [s]
                                // approximately aligned to the GPS time system. The;
                                // receiver local time of week number and leap second
                                // information can be used to translate the time to other; 
                                // time systems. More information about the difference in
                                // time systems can be found in RINEX 3 documentation.; 
                                // For a receiver operating in GLONASS only mode, UTC
                                // time can be determined by subtracting the leapS field; 
                                // from GPS time regardless of whether the GPS leap
                                // seconds are valid.; 
        uint16_t week;             // GPS week number in receiver local time. [weeks]
        int8_t leapS;              // GPS leap seconds (GPS-UTC). [s]
                                // This field represents the receiver's best knowledge of;
                                // the leap seconds offset. A flag is given in the
                                // recStat bitfield to indicate if the leap seconds; 
                                // are known.
        uint8_t numMeas;           // // of measurements to follow
        uint8_t recStat;           // Receiver tracking status bitfield
        static constexpr uint8_t REC_STAT_LEAP_SEC = 1;   // Leap seconds have been determined
        static constexpr uint8_t REC_STAT_CLK_RESET = 2;  // Clock reset applied. Typically the receiver  
                                      // clock is changed in increments of integer;
                                      // milliseconds.
        uint8_t version;           // Message version (0x01 for this version).
        std::array<uint8_t, 2> reserved1;      // Reserved
        
        std::vector<RxmRAWX_Meas> meas;

    };
}
