#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgANT {
        // CFG-ANT (0x06 0x13);
        // Antenna Control Settings
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 19;
        
        uint16_t flags;            // Antenna Flag Mask
        static constexpr uint16_t FLAGS_SVCS = 1;         // Enable Antenna Supply Voltage Control Signal
        static constexpr uint16_t FLAGS_SCD = 2;          // Enable Short Circuit Detection
        static constexpr uint16_t FLAGS_OCD = 4;          // Enable Open Circuit Detection
        static constexpr uint16_t FLAGS_PDWN_ON_SCD = 8;  // Power Down Antenna supply if Short Circuit is 
                                      // detected. (only in combination with Bit 1);
        static constexpr uint16_t FLAGS_RECOVERY = 16;    // Enable automatic recovery from short state
        
        uint16_t pins;             // Antenna Pin Configuration
        static constexpr uint16_t PIN_SWITCH_MASK = 31;    // PIO-Pin used for switching antenna supply 
                                       // (internal to TIM-LP/TIM-LF);
        static constexpr uint16_t PIN_SCD_MASK = 992;      // PIO-Pin used for detecting a short in the 
                                       // antenna supply;
        static constexpr uint16_t PIN_OCD_MASK = 31744;    // PIO-Pin used for detecting open/not connected 
                                       // antenna;
        static constexpr uint16_t PIN_RECONFIG = 32678;    // if set to one, and this command is sent to the 
                                       // receiver, the receiver will reconfigure the; 
                                       // pins as specified.

    };
}
