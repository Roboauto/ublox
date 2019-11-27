#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct RxmRAWX_Meas {
        // see message RxmRAWX;
        //
        
        double prMes;             // Pseudorange measurement [m]. GLONASS inter frequency
                                  // channel delays are compensated with an internal;
                                  // calibration table.
        double cpMes;             // Carrier phase measurement [L1 cycles]. The carrier
                                  // phase initial ambiguity is initialized using an;
                                  // approximate value to make the magnitude of
                                  // the phase close to the pseudorange;
                                  // measurement. Clock resets are applied to both
                                  // phase and code measurements in accordance;
                                  // with the RINEX specification.
        float doMes;             // Doppler measurement [Hz] (positive sign for
                                  // approaching satellites);
        uint8_t gnssId;              // GNSS identifier (see CfgGNSS for constants)
        
        uint8_t svId;                // Satellite identifier (see Satellite Numbering)
        
        uint8_t reserved0;           // Reserved
        
        uint8_t freqId;              // Only used for GLONASS: This is the frequency
                                  // slot + 7 (range from 0 to 13);
        uint16_t locktime;           // Carrier phase locktime counter [ms] 
                                  // (maximum 64500 ms);
        int8_t cno;                  // Carrier-to-noise density ratio (signal strength) 
                                  // [dB-Hz];
        uint8_t prStdev;             // Estimated pseudorange measurement standard
                                  // deviation [m / 0.01*2^n];
        uint8_t cpStdev;             // Estimated carrier phase measurement standard
                                  // deviation (note a raw value of 0x0F indicates the;
                                  // value is invalid) [cycles / 0.004]
        uint8_t doStdev;             // Estimated Doppler measurement standard deviation 
                                  // [Hz / 0.002*2^n];
        
        uint8_t trkStat;             // Tracking status bitfield
        static constexpr uint8_t TRK_STAT_PR_VALID = 1;       // Pseudorange valid
        static constexpr uint8_t TRK_STAT_CP_VALID = 2;       // Carrier phase valid
        static constexpr uint8_t TRK_STAT_HALF_CYC = 4;       // Half cycle valid
        static constexpr uint8_t TRK_STAT_SUB_HALF_CYC = 8;   // Half cycle subtracted from phase
        
        uint8_t reserved1;           // Reserved

    };
}
