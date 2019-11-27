#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct NavTIMEUTC {
        // NAV-TIMEUTC (0x01 0x21);
        // UTC Time Solution
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 33;
        
        uint32_t iTOW;             // GPS Millisecond time of week [ms]
        
        uint32_t tAcc;             // Time Accuracy Estimate [ns]
        int32_t nano;              // Fraction of second, range -1e9 .. 1e9 (UTC) [ns]
        uint16_t year;             // Year, range 1999..2099 (UTC) [y]
        uint8_t month;             // Month, range 1..12 (UTC) [month]
        uint8_t day;               // Day of Month, range 1..31 (UTC) [d]
        uint8_t hour;              // Hour of Day, range 0..23 (UTC) [h]
        uint8_t min;               // Minute of Hour, range 0..59 (UTC) [min]
        uint8_t sec;               // Seconds of Minute, range 0..60 (UTC) [s] (60 for 
                                // leap second);
        
        uint8_t valid;             // Validity Flags
        static constexpr uint8_t VALID_TOW = 1;         // Valid Time of Week
        static constexpr uint8_t VALID_WKN = 2;         // Valid Week Number
        static constexpr uint8_t VALID_UTC = 4;         // Valid Leap Seconds, i.e. Leap Seconds already known
        static constexpr uint8_t VALID_UTC_STANDARD_MASK = 240;  // UTC standard Identifier Bit mask:
        static constexpr uint8_t UTC_STANDARD_NOT_AVAILABLE = 0;    // Information not available
        static constexpr uint8_t UTC_STANDARD_CRL = 16;             // Communications Research Labratory
        static constexpr uint8_t UTC_STANDARD_NIST = 32;            // National Institute of Standards and 
                                                // Technology (NIST);
        static constexpr uint8_t UTC_STANDARD_USNO = 48;            // U.S. Naval Observatory (USNO)
        static constexpr uint8_t UTC_STANDARD_BIPM = 64;            // International Bureau of Weights and 
                                                // Measures (BIPM);
        static constexpr uint8_t UTC_STANDARD_EL = 80;              // European Laboratory (tbd)
        static constexpr uint8_t UTC_STANDARD_SU = 96;              // Former Soviet Union (SU)
        static constexpr uint8_t UTC_STANDARD_NTSC = 112;           // National Time Service Center, China
        static constexpr uint8_t UTC_STANDARD_UNKNOWN = 240;
    };
}
