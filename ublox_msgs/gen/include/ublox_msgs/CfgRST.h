#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgRST {
        // CFG-RST (0x06 0x04);
        // Reset Receiver / Clear Backup Data Structures
        //;
        // Don't expect this message to be acknowledged by the receiver.
        //  - Newer FW version won't acknowledge this message at all.;
        //  - Older FW version will acknowledge this message but the acknowledge may not
        //    be sent completely before the receiver is reset.;
        //
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 4; 
        
        uint16_t navBbrMask; // BBR Sections to clear. 
        // The following Special Sets apply:;
        static constexpr uint16_t NAV_BBR_HOT_START = 0;       // Hot start the device
        static constexpr uint16_t NAV_BBR_WARM_START = 1;      // Warm start the device
        static constexpr uint16_t NAV_BBR_COLD_START = 65535;  // Cold start the device
        static constexpr uint16_t NAV_BBR_EPH = 1;       // Ephemeris
        static constexpr uint16_t NAV_BBR_ALM = 2;       // Almanac
        static constexpr uint16_t NAV_BBR_HEALTH = 4;    // Health
        static constexpr uint16_t NAV_BBR_KLOB = 8;      // Klobuchar parameters
        static constexpr uint16_t NAV_BBR_POS = 16;      // Position
        static constexpr uint16_t NAV_BBR_CLKD = 32;     // Clock Drift
        static constexpr uint16_t NAV_BBR_OSC = 64;      // Oscillator Parameter
        static constexpr uint16_t NAV_BBR_UTC = 128;     // UTC Correction + GPS Leap Seconds Parameters
        static constexpr uint16_t NAV_BBR_RTC = 256;     // RTC
        static constexpr uint16_t NAV_BBR_AOP = 32768;   // Autonomous Orbit Parameters
        
        uint8_t resetMode;              // Reset Type:
        static constexpr uint8_t RESET_MODE_HW_IMMEDIATE = 0;       // Hardware reset (Watchdog) immediately
        static constexpr uint8_t RESET_MODE_SW = 1;                 // Controlled Software reset
        static constexpr uint8_t RESET_MODE_GNSS = 2;               // Controlled Software reset (GNSS only)
        static constexpr uint8_t RESET_MODE_HW_AFTER_SHUTDOWN = 4;  // Hardware reset (Watchdog) after 
                                                // shutdown;
        static constexpr uint8_t RESET_MODE_GNSS_STOP = 8;          // Controlled GNSS stop
        static constexpr uint8_t RESET_MODE_GNSS_START = 9;         // Controlled GNSS start
        
        uint8_t reserved1;     // Reserved
    };
}
