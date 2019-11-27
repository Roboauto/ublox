#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct AidHUI {
        // AID-HUI (0x0B 0x02);
        // GPS Health, UTC and ionosphere parameters
        //;
        // All UBX-AID messages are deprecated; use UBX-MGA messages instead.
        // This message contains a health bit mask, UTC time and Klobuchar parameters. For more;
        // information on these parameters, please see the ICD-GPS-200 documentation.
        
        static constexpr uint8_t CLASS_ID = 11;
        static constexpr uint8_t MESSAGE_ID = 2;
        
        uint32_t  health;          // Bitmask, every bit represents a GPS SV (1-32). 
                                // If the bit is set the SV is healthy.;
        double utcA0;           // UTC - parameter A0
        double utcA1;           // UTC - parameter A1
        int32_t   utcTOW;          // UTC - reference time of week
        int16_t   utcWNT;          // UTC - reference week number
        int16_t   utcLS;           // UTC - time difference due to leap seconds before event
        int16_t   utcWNF;          // UTC - week number when next leap second event occurs
        int16_t   utcDN;           // UTC - day of week when next leap second event occurs
        int16_t   utcLSF;          // UTC - time difference due to leap seconds after event
        int16_t   utcSpare;        // UTC - Spare to ensure structure is a multiple of 4 
                                // bytes;
        float klobA0;          // Klobuchar - alpha 0 [s]
        float klobA1;          // Klobuchar - alpha 1 [s/semicircle]
        float klobA2;          // Klobuchar - alpha 2 [s/semicircle^2]
        float klobA3;          // Klobuchar - alpha 3 [s/semicircle^3]
        float klobB0;          // Klobuchar - beta 0  [s]
        float klobB1;          // Klobuchar - beta 1  [s/semicircle]
        float klobB2;          // Klobuchar - beta 2  [s/semicircle^2]
        float klobB3;          // Klobuchar - beta 3  [s/semicircle^3]
        uint32_t flags;            // flags
        static constexpr uint32_t FLAGS_HEALTH = 1;     // Healthmask field in this message is valid
        static constexpr uint32_t FLAGS_UTC = 2;        // UTC parameter fields in this message are valid
        static constexpr uint32_t FLAGS_KLOB = 4;       // Klobuchar parameter fields in this message are 
                                    // valid;

    };
}
