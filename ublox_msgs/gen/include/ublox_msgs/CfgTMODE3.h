#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgTMODE3 {
        // CFG-TMODE3 (0x06, 0x71);
        // Time Mode Settings 3
        //;
        // Configures the receiver to be in Time Mode. The position referred to in this
        // message is that of the Antenna Reference Point (ARP). See the Time Mode; 
        // Description for details.
        //; 
        // Supported on:
        //  - u-blox 8 / u-blox M8 with protocol version 20 (only with High Precision;
        //    GNSS products)
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 113;
        
        uint8_t version;                     // Message version (0x00 for this version)
        uint8_t reserved1;                   // Reserved
        
        uint16_t flags;
        static constexpr uint16_t FLAGS_MODE_MASK = 255;      // Receiver Mode:
        static constexpr uint16_t FLAGS_MODE_DISABLED = 0;      // Disabled
        static constexpr uint16_t FLAGS_MODE_SURVEY_IN = 1;     // Survey In
        static constexpr uint16_t FLAGS_MODE_FIXED = 2;         // Fixed Mode (true ARP position required)
        static constexpr uint16_t FLAGS_LLA = 256;            // Position is given in LAT/LON/ALT 
                                          // (default is ECEF);
        
        int32_t ecefXOrLat;                  // WGS84 ECEF X coordinate (or latitude) of
                                          // the ARP position, depending on flags above;
                                          // [cm] or [deg / 1e-7]
        int32_t ecefYOrLon;                  // WGS84 ECEF Y coordinate (or longitude) of
                                          // the ARP position, depending on flags above;
                                          // [cm] or [deg / 1e-7]
        int32_t ecefZOrAlt;                  // WGS84 ECEF Z coordinate (or altitude) of
                                          // the ARP position, depending on flags above;
                                          // [cm]
        int8_t ecefXOrLatHP;                 // High-precision WGS84 ECEF X coordinate (or
                                          // latitude) of the ARP position, depending on;
                                          // flags above. Must be in the range -99..+99.
                                          // The precise WGS84 ECEF X coordinate in units;
                                          // of cm, or the precise WGS84 ECEF latitude in
                                          // units of 1e-7 degrees, is given by;
                                          // ecefXOrLat + (ecefXOrLatHP * 1e-2)
                                          // [0.1 mm] or [deg * 1e-9];
        int8_t ecefYOrLonHP;                 // High-precision WGS84 ECEF Y coordinate (or
                                          // longitude) of the ARP position, depending on;
                                          // flags above. Must be in the range -99..+99.
                                          // The precise WGS84 ECEF Y coordinate in units;
                                          // of cm, or the precise WGS84 ECEF longitude 
                                          // in units of 1e-7 degrees, is given by;
                                          // ecefYOrLon + (ecefYOrLonHP * 1e-2)
                                          // [0.1 mm] or [deg * 1e-9];
        int8_t ecefZOrAltHP;                 // High-precision WGS84 ECEF Z coordinate (or
                                          // altitude) of the ARP position, depending on;
                                          // flags above. Must be in the range -99..+99.
                                          // The precise WGS84 ECEF Z coordinate, or;
                                          // altitude coordinate, in units of cm is given
                                          // by ecefZOrAlt + (ecefZOrAltHP * 1e-2);
                                          // [0.1 mm]
        uint8_t reserved2;                   // Reserved
        
        uint32_t fixedPosAcc;                // Fixed position 3D accuracy
                                          // [0.1 mm];
        uint32_t svinMinDur;                 // Survey-in minimum duration
                                          // [s];
        uint32_t svinAccLimit;               // Survey-in position accuracy limit
                                          // [0.1 mm];
        
        std::array<uint8_t, 8> reserved3;                // Reserved

    };
}
