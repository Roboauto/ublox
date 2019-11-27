#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct CfgGNSS_Block {
        // see Cfg-GNSS message;
        //
        
        uint8_t gnssId;            // System identifier (see Satellite Numbering)
        
        static constexpr uint8_t GNSS_ID_GPS = 0;
        static constexpr uint8_t GNSS_ID_SBAS = 1;
        static constexpr uint8_t GNSS_ID_GALILEO = 2;
        static constexpr uint8_t GNSS_ID_BEIDOU = 3;
        static constexpr uint8_t GNSS_ID_IMES = 4;
        static constexpr uint8_t GNSS_ID_QZSS = 5;
        static constexpr uint8_t GNSS_ID_GLONASS = 6;
        
        uint8_t resTrkCh;          // (Read only in protocol versions greater than 23)
                                // Number of reserved (minimum) tracking channels; 
                                // for this GNSS system
        static constexpr uint8_t RES_TRK_CH_GPS = 8;
        static constexpr uint8_t RES_TRK_CH_QZSS = 0;
        static constexpr uint8_t RES_TRK_CH_SBAS = 0;
        static constexpr uint8_t RES_TRK_CH_GLONASS = 8;
        uint8_t maxTrkCh;          // (Read only in protocol versions greater than 23)
                                // Maximum number of tracking channels used for this; 
                                // system. Must be > 0, >= resTrkChn, <= numTrkChUse and
                                // <= maximum number of tracking channels supported for; 
                                // this system
        static constexpr uint8_t MAX_TRK_CH_MAJOR_MIN = 4;         // maxTrkCh must have this minimum value
                                               // for each enabled major GNSS;
        static constexpr uint8_t MAX_TRK_CH_GPS = 16;
        static constexpr uint8_t MAX_TRK_CH_GLONASS = 14;
        static constexpr uint8_t MAX_TRK_CH_QZSS = 3;
        static constexpr uint8_t MAX_TRK_CH_SBAS = 3;
        
        uint8_t reserved1;         // Reserved
        
        uint32_t flags;            // Bitfield of flags. At least one signal must be
                                // configured in every enabled system.; 
        static constexpr uint32_t FLAGS_ENABLE = 1;                // Enable this system
        static constexpr uint32_t FLAGS_SIG_CFG_MASK = 16711680;   // Signal configuration mask
        static constexpr uint32_t SIG_CFG_GPS_L1CA = 65536;        // When gnssId is 0 (GPS)
                                               // * 0x01 = GPS L1C/A;
        static constexpr uint32_t SIG_CFG_SBAS_L1CA = 65536;       // When gnssId is 1 (SBAS)
                                               // * 0x01 = SBAS L1C/A;
        static constexpr uint32_t SIG_CFG_GALILEO_E1OS = 65536;    // When gnssId is 2 (Galileo)
                                               // * 0x01 = Galileo E1OS (not supported in; 
                                               //   protocol versions less than 18)
        static constexpr uint32_t SIG_CFG_BEIDOU_B1I = 65536;      // When gnssId is 3 (BeiDou)
                                               // * 0x01 = BeiDou B1I; 
        static constexpr uint32_t SIG_CFG_IMES_L1 = 65536;         // When gnssId is 4 (IMES)
                                               // * 0x01 = IMES L1;
        static constexpr uint32_t SIG_CFG_QZSS_L1CA = 65536;       // When gnssId is 5 (QZSS)
                                               // * 0x01 = QZSS L1C/A;
        static constexpr uint32_t SIG_CFG_QZSS_L1SAIF = 262144;    // * 0x04 = QZSS L1SAIF
        static constexpr uint32_t SIG_CFG_GLONASS_L1OF = 65536;    // When gnssId is 6 (GLONASS)
                                               // * 0x01 = GLONASS L1OF;
    };
}
