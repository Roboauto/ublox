#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgSBAS {
        // CFG-SBAS (0x06 0x16);
        // SBAS Configuration
        //;
        // This message configures the SBAS receiver subsystem (i.e. WAAS, EGNOS, MSAS).
        // See the SBAS Configuration Settings Description for a detailed description of;
        // how these settings affect receiver operation
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 22;
        
        uint8_t mode;              // SBAS Mode
        static constexpr uint8_t MODE_ENABLED = 1;    // SBAS Enabled (1) / Disabled (0)
                                  //  This field is deprecated; use UBX-CFG-GNSS to; 
                                  // enable/disable SBAS operation
        static constexpr uint8_t MODE_TEST = 2;       // SBAS Testbed: Use data anyhow (1) / Ignore data when 
                                  // in Test Mode (SBAS Msg 0);
        
        uint8_t usage;             // SBAS Usage
        static constexpr uint8_t USAGE_RANGE = 1;     // Use SBAS GEOs as a ranging source (for navigation)
        static constexpr uint8_t USAGE_DIFF_CORR = 2; // Use SBAS Differential Corrections
        static constexpr uint8_t USAGE_INTEGRITY = 4; // Use SBAS Integrity Information
        
        uint8_t maxSBAS;           // Maximum Number of SBAS prioritized tracking
                                // channels (valid range: 0 - 3) to use;
                                // (obsolete and superseeded by UBX-CFG-GNSS in protocol
                                // versions 14+).;
        
        
        uint8_t scanmode2;         // Continuation of scanmode bitmask below
                                // PRN 152...158;
        uint32_t scanmode1;        // Which SBAS PRN numbers to search for (Bitmask)
                                // If all Bits are set to zero, auto-scan (i.e. all valid;
                                // PRNs) are searched. Every bit corresponds to a PRN 
                                // number.;
                                // PRN 120..151

    };
}
