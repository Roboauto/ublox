#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct UpdSOS {
        // UPD-SOS (0x09 0x14);
        //
        // Firmware Supported on:;
        // u-blox 8 / u-blox M8 from protocol version 15 up to version 23.01
        //;
        
        static constexpr uint8_t CLASS_ID = 9;
        static constexpr uint8_t MESSAGE_ID = 20;
        
        uint8_t cmd;                   // Command
        // The host can send this message in order to save part of the BBR memory in a; 
        // file in flash file system. The feature is designed in order to emulate the 
        // presence of the backup battery even if it is not present; the host can issue; 
        // the save on shutdown command before switching off the device supply. It is 
        // recommended to issue a GNSS stop command before, in order to keep the BBR; 
        // memory content consistent.
        static constexpr uint8_t CMD_FLASH_BACKUP_CREATE = 0;    // Create Backup File in Flash
        // The host can send this message in order to erase the backup file present in; 
        // flash. It is recommended that the clear operation is issued after the host has 
        // received the notification that the memory has been restored after a reset.; 
        // Alternatively the host can parse the startup string 'Restored data saved on 
        // shutdown' or poll the UBX-UPD-SOS message for getting the status.;
        static constexpr uint8_t CMD_FLASH_BACKUP_CLEAR = 1;     // Clear Backup File in Flash
        
        std::array<uint8_t, 3> reserved1;          // Reserved
    };
}
