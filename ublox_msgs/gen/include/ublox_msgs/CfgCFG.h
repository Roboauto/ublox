#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgCFG {
        // CFG-CFG (0x06 0x09);
        // Clear, Save and Load configurations
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 9;
        
        uint32_t clearMask;          // Mask with configuration sub-sections to Clear
                                  // (=Load Default Configurations to Permanent;
                                  // Configurations in non-volatile memory)
        uint32_t saveMask;           // Mask with configuration sub-section to Save
                                  // (=Save Current Configuration to Non-volatile;
                                  // Memory)
        uint32_t loadMask;           // Mask with configuration sub-sections to Load
                                  // (=Load Permanent Configurations from;
                                  // Non-volatile Memory to Current Configurations)
        
        static constexpr uint32_t MASK_IO_PORT = 1;       // Communications port settings. Modifying this 
                                      // sub-section results in an IO system reset.; 
                                      // Because of this undefined data may be output 
                                      // for a short period of time after receiving the;
                                      // message.
        static constexpr uint32_t MASK_MSG_CONF = 2;      // Message Configuration
        static constexpr uint32_t MASK_INF_MSG = 4;       // INF Message Configuration
        static constexpr uint32_t MASK_NAV_CONF = 8;      // Navigation Configuration
        static constexpr uint32_t MASK_RXM_CONF = 16;     // Receiver Manager Configuration
        static constexpr uint32_t MASK_SEN_CONF = 256;    // Sensor Interface Configuration, protocol >= 19
        static constexpr uint32_t MASK_RINV_CONF = 512;   // Remote Inventory Configuration
        static constexpr uint32_t MASK_ANT_CONF = 1024;   // Antenna Configuration
        static constexpr uint32_t MASK_LOG_CONF = 2048;   // Logging Configuration
        static constexpr uint32_t MASK_FTS_CONF = 4096;   // FTS Configuration. Only applicable to the 
                                      // FTS product variant.;
        
        uint8_t deviceMask;          // Mask which selects the devices for this command
        static constexpr uint8_t DEV_BBR = 1;             // device battery backed RAM
        static constexpr uint8_t DEV_FLASH = 2;           // device Flash
        static constexpr uint8_t DEV_EEPROM = 4;          // device EEPROM
        static constexpr uint8_t DEV_SPI_FLASH = 16;      // device SPI Flash

    };
}
