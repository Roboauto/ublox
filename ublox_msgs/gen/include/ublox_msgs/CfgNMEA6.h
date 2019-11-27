#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgNMEA6 {
        // CFG-NMEA (0x06 0x17);
        // NMEA protocol configuration
        //;
        // Set/Get the NMEA protocol configuration. See section NMEA Protocol 
        // Configuration for a detailed description of the configuration effects on; 
        // NMEA output
        //;
        // Supported on u-blox 6 from firmware version 6.00 up to version 7.03.
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 23; 
        
        uint8_t filter;                  // filter flags
        static constexpr uint8_t FILTER_POS = 1;          // Disable position filtering
        static constexpr uint8_t FILTER_MSK_POS = 2;      // Disable masked position filtering
        static constexpr uint8_t FILTER_TIME = 4;         // Disable time filtering
        static constexpr uint8_t FILTER_DATE = 8;         // Disable date filtering
        static constexpr uint8_t FILTER_SBAS_FILT = 16;   // Enable SBAS filtering
        static constexpr uint8_t FILTER_TRACK = 32;       // Disable track filtering
        
        uint8_t version;             // NMEA version
        static constexpr uint8_t NMEA_VERSION_2_3 = 35;     // Version 2.3
        static constexpr uint8_t NMEA_VERSION_2_1 = 33;     // Version 2.1
        
        uint8_t numSV;                   // Maximum Number of SVs to report in NMEA
                                      // protocol.;
                                      // This does not affect the receiver's operation.
                                      // It only limits the number of SVs reported in;
                                      // NMEA mode (this might be needed with older
                                      // mapping applications which only support 8- or;
                                      // 12-channel receivers)
        
        uint8_t flags;                   // flags
        static constexpr uint8_t FLAGS_COMPAT = 1;          // enable compatibility mode.
                                        // This might be needed for certain applications;  
                                        // when customer's NMEA parser expects a fixed 
                                        // number of  digits in position coordinates;
        static constexpr uint8_t FLAGS_CONSIDER = 2;        // enable considering mode

    };
}
