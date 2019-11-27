#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct MonHW6 {
        // MON-HW (0x0A 0x09);
        // Hardware Status
        // Firmware 6;
        //
        // Status of different aspect of the hardware, such as Antenna, PIO/Peripheral; 
        // Pins, Noise Level, Automatic Gain Control (AGC)
        //;
        // WARNING: this message is a different length than the MonHW message for
        // firmware version 7 & 8;
        
        static constexpr uint8_t CLASS_ID = 10;
        static constexpr uint8_t MESSAGE_ID = 9;
        
        uint32_t pinSel;                 // Mask of Pins Set as Peripheral/PIO
        uint32_t pinBank;                // Mask of Pins Set as Bank A/B
        uint32_t pinDir;                 // Mask of Pins Set as Input/Output
        uint32_t pinVal;                 // Mask of Pins Value Low/High
        uint16_t noisePerMS;             // Noise Level as measured by the GPS Core
        uint16_t agcCnt;                 // AGC Monitor (counts SIGHI xor SIGLO, 
                                      // range 0 to 8191);
        uint8_t aStatus;                 // Status of the Antenna Supervisor State Machine 
        static constexpr uint8_t A_STATUS_INIT = 0;
        static constexpr uint8_t A_STATUS_UNKNOWN = 1;
        static constexpr uint8_t A_STATUS_OK = 2;
        static constexpr uint8_t A_STATUS_SHORT = 3;
        static constexpr uint8_t A_STATUS_OPEN = 4;
        
        uint8_t aPower;                  // Current PowerStatus of Antenna 
        static constexpr uint8_t A_POWER_OFF = 0; 
        static constexpr uint8_t A_POWER_ON = 1;
        static constexpr uint8_t A_POWER_UNKNOWN = 2;
        
        uint8_t flags;                   // Flags:
        static constexpr uint8_t FLAGS_RTC_CALIB = 1;            // RTC is calibrated
        static constexpr uint8_t FLAGS_SAFE_BOOT =  2;           // Safe boot mode (0 = inactive, 1 = active)
        static constexpr uint8_t FLAGS_JAMMING_STATE_MASK = 12;  // output from Jamming/Interference Monitor: 
        static constexpr uint8_t JAMMING_STATE_UNKNOWN_OR_DISABLED = 0;   // unknown or feature disabled
        static constexpr uint8_t JAMMING_STATE_OK = 4;                    // ok - no significant jamming
        static constexpr uint8_t JAMMING_STATE_WARNING = 8;               // interference visible but fix OK
        static constexpr uint8_t JAMMING_STATE_CRITICAL = 12;             // interference visible and no fix
        static constexpr uint8_t FLAGS_XTAL_ABSENT =  16;        // RTC XTAL is absent
                                             // (not supported in protocol versions < 18);
        uint8_t reserved0;               // Reserved
        uint32_t usedMask;               // Mask of Pins that are used by the Virtual Pin 
                                      // Manager;
        std::array<uint8_t, 25> VP;                  // Array of Pin Mappings for each of the 25  
                                      // Physical Pins;
        uint8_t jamInd;                  // CW Jamming indicator, scaled:
        static constexpr uint8_t JAM_IND_NONE = 0;          // No CW Jamming
        static constexpr uint8_t JAM_IND_STRONG = 255;      // Strong CW Jamming    
        
        std::array<uint8_t, 2> reserved1;            // Reserved
        
        uint32_t pinIrq;                 // Mask of Pins Value using the PIO Irq
        uint32_t pullH;                  // Mask of Pins Value using the PIO Pull High 
                                      // Resistor;
        uint32_t pullL;                  // Mask of Pins Value using the PIO Pull Low 
                                      // Resistor;
    };
}
