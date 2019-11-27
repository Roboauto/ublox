#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgNAVX5 {
        // CFG-NAVX5 (0x06 0x23);
        // Navigation Engine Expert Settings
        //;
        // Warning: Refer to u-blox protocol spec before changing these settings.
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 35;
        
        uint16_t version;        // Message version (set to 0)
        
        uint16_t mask1;          // First parameters bitmask (possible values below)
        static constexpr uint16_t MASK1_MIN_MAX        = 4;        // apply min/max SVs settings
        static constexpr uint16_t MASK1_MIN_CNO        = 8;        // apply minimum C/N0 setting
        static constexpr uint16_t MASK1_INITIAL_FIX_3D = 64;       // apply initial 3D fix settings
        static constexpr uint16_t MASK1_WKN_ROLL       = 512;      // apply GPS week number rollover settings
        static constexpr uint16_t MASK1_ACK_AID        = 1024;     // apply assistance acknowledgment 
                                               // settings;
        static constexpr uint16_t MASK1_PPP            = 8192;     // apply usePPP flag
        static constexpr uint16_t MASK1_AOP            = 16384;    // apply aopCfg (useAOP flag) and 
                                               // aopOrbMaxErr settings;
                                               // (AssistNow Autonomous)
        
        uint32_t mask2;          // Second parameters bitmask (possible values below)
                              // Firmware >=8 only;
        static constexpr uint32_t MASK2_ADR = 64;                    // Apply ADR sensor fusion on/off 
                                                 // setting;
        static constexpr uint32_t MASK2_SIG_ATTEN_COMP_MODE = 128;   // Apply signal attenuation 
                                                 // compensation feature settings;
        
        std::array<uint8_t, 2> reserved1;      // Always set to zero
        
        uint8_t minSVs;            // Minimum number of satellites for navigation
        uint8_t maxSVs;            // Maximum number of satellites for navigation
        uint8_t minCNO;            // Minimum satellite signal level for navigation [dBHz]
        
        uint8_t reserved2;         // Always set to zero
        
        uint8_t iniFix3D;          // If set to 1, initial fix must be 3D
        
        std::array<uint8_t, 2> reserved3;      // Always set to zero
        
        uint8_t ackAiding;         // If set to 1, issue acknowledgments for assistance
        uint16_t wknRollover;      // GPS week rollover number, GPS week numbers will be set 
                                // correctly from this week up to 1024 weeks after this; 
                                // week
        uint8_t sigAttenCompMode;  // Permanently attenuated signal compensation [dBHz]
                                // 0 = disabled, 255 = automatic;
                                // 1..63 = maximum expected C/N0 value
                                // Firmware 8 only;
        
        std::array<uint8_t, 5> reserved4;      // Always set to zero
        
        uint8_t usePPP;            // Enable/disable PPP (on supported units)
        uint8_t aopCfg;            // AssistNow Autonomous configuration, 1: enabled
        
        std::array<uint8_t, 2> reserved5;      // Always set to zero
        
        uint16_t aopOrbMaxErr;     // Maximum acceptable (modeled) autonomous orbit 
                                // error [m];
                                // valid range = 5..1000
                                // 0 = reset to firmware default;
        
        std::array<uint8_t, 7> reserved6;      // Always set to zero
        
        uint8_t useAdr;            // Enable/disable ADR sensor fusion 
                                // 1: enabled, 0: disabled;
                                // Only supported on certain products 

    };
}
