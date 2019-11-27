#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct MgaGAL {
        // MGA-GAL (0x13 0x02);
        // Galileo Ephemeris Assistance
        //;
        // This message allows the delivery of Galileo ephemeris assistance to a 
        // receiver. See the description of AssistNow Online for details.;
        // 
        
        static constexpr uint8_t CLASS_ID = 19;
        static constexpr uint8_t MESSAGE_ID = 2;
        
        uint8_t type;              // Message type (0x01 for this type)
        uint8_t version;           // Message version (0x00 for this version)
        uint8_t svid;              // Galileo Satellite identifier
        
        uint8_t reserved0;         // Reserved
        
        uint16_t iodNav;           // Ephemeris and clock correction issue of Data
        int16_t deltaN;            // Mean motion difference from computed value 
                                // [semi-cir cles/s * 2^-43];
        int32_t m0;                // Mean anomaly at reference time [semi-cir cles 2^-31]
        uint32_t e;                // Eccentricity [2^-33]
        uint32_t sqrtA;            // Square root of the semi-major axis [m^0.5 * 2^-19]
        int32_t omega0;            // Longitude of ascending node of orbital plane at weekly
                                // epoch [semi-cir cles 2^-31];
        int32_t i0;                // inclination angle at reference time 
                                // [semi-cir cles 2^-31];
        int32_t omega;             // Argument of perigee [semi-cir cles 2^-31]
        int32_t omegaDot;          // Rate of change of right ascension 
                                // [semi-cir cles/s 2^-43];
        int16_t iDot;              // Rate of change of inclination angle 
                                // [semi-cir cles/s 2^-43];
        int16_t cuc;               // Amplitude of the cosine harmonic correction term to 
                                // the argument of latitude [radians * 2^-29];
        int16_t cus;               // Amplitude of the sine harmonic correction term to 
                                // the argument of latitude [radians * 2^-29];
        int16_t crc;               // Amplitude of the cosine harmonic correction term 
                                // to the orbit radius [radians * 2^-5];
        int16_t crs;               // Amplitude of the sine harmonic correction term to the 
                                // orbit radius [radians * 2^-5];
        int16_t cic;               // Amplitude of the cosine harmonic correction term to 
                                // the angle of inclination [radians * 2^-29];
        int16_t cis;               // Amplitude of the sine harmonic correction term to the 
                                // angle of inclination [radians * 2^-29];
        uint16_t toe;              // Ephemeris reference time [60 * s]
        int32_t af0;               // clock bias correction coefficient [s * 2^-34]
        int32_t af1;               // SV clock drift correction coefficient [s/s * 2^-46]
        int8_t af2;               // SV clock drift rate correction coefficient 
                                // [s/s^2 * 2^-59];
        uint8_t sisaindexE1E5b;   // Signal-in-Space Accuracy index for dual frequency 
                                // E1-E5b;
        uint16_t toc;              // Clock correction data reference Time of Week [60 * s]
        int16_t bgdE1E5b;          // E1-E5b Broadcast Group Delay
        
        std::array<uint8_t, 2> reserved1;     // Reserved
        
        uint8_t healthE1B;        // E1-B Signal Health Status
        uint8_t dataValidityE1B;  // E1-B Data Validity Status
        uint8_t healthE5b;        // E5b Signal Health Status
        uint8_t dataValidityE5b;  // E5b Data Validity Status
        
        std::array<uint8_t, 4> reserved2;     // Reserved
    };
}
