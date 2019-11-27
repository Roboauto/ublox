#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct UpdSOS_Ack {
        // UPD-SOS (0x09 0x14);
        //
        // Backup File Creation Acknowledge / System Restored from Backup;
        // 
        // Firmware Supported on:;
        // u-blox 8 / u-blox M8 from protocol version 15 up to version 23.01
        //;
        
        static constexpr uint8_t CLASS_ID = 9;
        static constexpr uint8_t MESSAGE_ID = 20;
        
        uint8_t cmd;                   // Command
        static constexpr uint8_t CMD_BACKUP_CREATE_ACK = 2;   // Backup File Creation Acknowledge
                                          // The message is sent from the device as; 
                                          // confirmation of creation of a backup file 
                                          // in flash. The host can safely shut down the; 
                                          // device after received this message.
        static constexpr uint8_t CMD_SYSTEM_RESTORED = 3;     // System Restored from Backup
                                          // The message is sent from the device to; 
                                          // notify the host the BBR has been restored 
                                          // from a backup file in flash. The host; 
                                          // should clear the backup file after 
                                          // receiving this message. If the UBX-UPD-SOS; 
                                          // message is polled, this message will be 
                                          // present.;
        
        std::array<uint8_t, 3> reserved0;          // Reserved
        
        uint8_t response;                                  // Response:
        static constexpr uint8_t BACKUP_CREATE_NACK = 0;                      // Not acknowledged
        static constexpr uint8_t BACKUP_CREATE_ACK = 1;                       // Acknowledged
        static constexpr uint8_t SYSTEM_RESTORED_RESPONSE_UNKNOWN = 0;        // Unknown
        static constexpr uint8_t SYSTEM_RESTORED_RESPONSE_FAILED = 1;         // Failed restoring from backup 
                                                          // file;
        static constexpr uint8_t SYSTEM_RESTORED_RESPONSE_RESTORED = 2;       // Restored from backup file
        static constexpr uint8_t SYSTEM_RESTORED_RESPONSE_NOT_RESTORED = 3;   // Not restored (no backup)
        
        std::array<uint8_t, 3> reserved1;          // Reserved
    };
}
