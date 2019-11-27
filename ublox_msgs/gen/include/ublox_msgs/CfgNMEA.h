#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct CfgNMEA {
        // CFG-NMEA (0x06 0x17);
        // NMEA protocol configuration V1
        //;
        // Set/Get the NMEA protocol configuration. See section NMEA Protocol 
        // Configuration for a detailed description of the configuration effects on; 
        // NMEA output
        //;
        
        static constexpr uint8_t CLASS_ID = 6;
        static constexpr uint8_t MESSAGE_ID = 23; 
        
        uint8_t filter;                  // filter flags
        static constexpr uint8_t FILTER_POS = 1;          // Enable position output for failed or 
                                      // invalid fixes;
        static constexpr uint8_t FILTER_MSK_POS = 2;      // Enable position output for invalid fixes
        static constexpr uint8_t FILTER_TIME = 4;         // Enable time output for invalid times
        static constexpr uint8_t FILTER_DATE = 8;         // Enable date output for invalid dates
        static constexpr uint8_t FILTER_GPS_ONLY = 16;    // Restrict output to GPS satellites only
        static constexpr uint8_t FILTER_TRACK = 32;       // Enable COG output even if COG is frozen
        
        uint8_t nmeaVersion;             // NMEA version
        static constexpr uint8_t NMEA_VERSION_4_1 = 65;     // Version 4.1
        static constexpr uint8_t NMEA_VERSION_4_0 = 64;     // Version 4.0
        static constexpr uint8_t NMEA_VERSION_2_3 = 35;     // Version 2.3
        static constexpr uint8_t NMEA_VERSION_2_1 = 33;     // Version 2.1
        
        uint8_t numSV;                   // Maximum Number of SVs to report per TalkerId: 
                                      // unlimited (0) or 8, 12, 16;
        static constexpr uint8_t NUM_SV_UNLIMITED = 0; 
        
        uint8_t flags;                   // flags
        static constexpr uint8_t FLAGS_COMPAT = 1;          // enable compatibility mode.
                                        // This might be needed for certain applications;  
                                        // when customer's NMEA parser expects a fixed 
                                        // number of  digits in position coordinates;
        static constexpr uint8_t FLAGS_CONSIDER = 2;        // enable considering mode
        static constexpr uint8_t FLAGS_LIMIT82 = 4;         // enable strict limit to 82 characters maximum
        static constexpr uint8_t FLAGS_HIGH_PREC = 8;       // enable high precision mode
                                        // This flag cannot be set in conjunction with;  
                                        // either Compatibility Mode or Limit82 Mode.
                                        // (not supported in protocol versions < 20.01);
        
        uint32_t gnssToFilter;           // Filters out satellites based on their GNSS.  
                                      // If a bitfield is enabled, the corresponding; 
                                      // satellites will be not output.
        static constexpr uint32_t GNSS_TO_FILTER_GPS = 1;       // Disable reporting of GPS satellites
        static constexpr uint32_t GNSS_TO_FILTER_SBAS = 2;      // Disable reporting of SBAS satellites
        static constexpr uint32_t GNSS_TO_FILTER_QZSS = 16;     // Disable reporting of QZSS satellites
        static constexpr uint32_t GNSS_TO_FILTER_GLONASS = 32;  // Disable reporting of GLONASS satellites
        static constexpr uint32_t GNSS_TO_FILTER_BEIDOU = 64;   // Disable reporting of BeiDou satellites
        
        uint8_t svNumbering;             // Configures the display of satellites that do not  
                                      // have an NMEA-defined value. Note: this does not;
                                      // apply to satellites with an unknown ID.
        static constexpr uint8_t SV_NUMBERING_STRICT = 0;     // Strict - Satellites are not output
        static constexpr uint8_t SV_NUMBERING_EXTENDED = 1;   // Extended - Use proprietary numbering
        
        uint8_t mainTalkerId;            // By default the main Talker ID (i.e. the Talker 
                                      // ID used  for all messages other than GSV) is; 
                                      // determined by the  GNSS assignment of the 
                                      // receiver's channels (see CfgGNSS).; 
                                      // This field enables the main Talker ID to be 
                                      // overridden;
        static constexpr uint8_t MAIN_TALKER_ID_NOT_OVERRIDDEN = 0;   // Main Talker ID is not overridden
        static constexpr uint8_t MAIN_TALKER_ID_GP = 1;               // Set main Talker ID to 'GP'
        static constexpr uint8_t MAIN_TALKER_ID_GL = 2;               // Set main Talker ID to 'GL'
        static constexpr uint8_t MAIN_TALKER_ID_GN = 3;               // Set main Talker ID to 'GN'
        static constexpr uint8_t MAIN_TALKER_ID_GA = 4;               // Set main Talker ID to 'GA'
        static constexpr uint8_t MAIN_TALKER_ID_GB = 5;               // Set main Talker ID to 'GB'
        
        uint8_t gsvTalkerId;             // By default the Talker ID for GSV messages is  
                                      // GNSS specific (as defined by NMEA). This field; 
                                      // enables the GSV Talker ID to be overridden.
        static constexpr uint8_t GSV_TALKER_ID_GNSS_SPECIFIC = 0;   // Use GNSS specific Talker ID 
                                                // (as defined by NMEA);
        static constexpr uint8_t GSV_TALKER_ID_MAIN = 1;            // Use the main Talker ID
        
        uint8_t version;                 // Message version (set to 1 for this version)
        static constexpr uint8_t VERSION = 1;
        
        std::array<uint8_t, 2> bdsTalkerId;          // Sets the two characters that should be used 
                                      // for the BeiDou Talker ID. If these are set to; 
                                      // zero, the default BeiDou TalkerId will be used
        
        std::array<uint8_t, 6> reserved1;            // Reserved
    };
}
