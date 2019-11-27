#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgUSB {
        // UBX-CFG-USB (0x06 0x1B);
        // USB Configuration
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 27; 
        
        uint16_t vendorID;             // Only set to registered Vendor IDs.                     
                                    // Changing this field requires special Host drivers.;
        
        uint16_t productID;            // Product ID. Changing this field requires special  
                                    // Host drivers.;
        
        std::array<uint8_t, 2> reserved1;          // Reserved
        std::array<uint8_t, 2> reserved2;          // Reserved
        
        uint16_t powerConsumption;     // Power consumed by the device [mA]
        
        uint16_t flags;                // various configuration flags (see graphic below)
        static constexpr uint16_t FLAGS_RE_ENUM = 0;       // force re-enumeration
        static constexpr uint16_t FLAGS_POWER_MODE = 2;    // self-powered (1), bus-powered (0)
        
        std::array<int8_t, 32> vendorString;      // String containing the vendor name. 
                                   // 32 ASCII bytes including 0-termination.;
        std::array<int8_t, 32> productString;     // String containing the product name. 
                                   // 32 ASCII bytes including 0-termination.;
        std::array<int8_t, 32> serialNumber;      // String containing the serial number. 
                                   // 32 ASCII bytes including 0-termination.; 
                                   // Changing the String fields requires special Host 
                                   // drivers.;
    };
}
