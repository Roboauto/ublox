#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct RxmSFRB {
        // RXM-SFRB (0x02 0x11);
        // Subframe Buffer
        //;
        // The content of one single subframe buffer
        // For GPS satellites, the 10 dwrd values contain the parity checked subframe; 
        // data for 10 Words. Each dwrd has 24 Bits with valid data (Bits 23 to 0). The 
        // remaining 8 bits (31 to 24) have an undefined value. The direction within the; 
        // Word is that the higher order bits are received from the SV first. Example: 
        // The Preamble can be found in std::array<dwrd, 0> , at bit position 23 down to 16. For more; 
        // details on the data format please refer to the ICD-GPS-200C
        // Interface document.;
        // For SBAS satellites, the 250 Bit message block can be found in std::array<dwrd, 0> to 
        // std::array<dwrd, 6> for the first 224 bits. The remaining 26 bits are in std::array<dwrd, 7> , whereas;
        // Bits 25 and 24 are the last two data bits, and Bits 23 down to 0 are the
        // parity bits. For more information on SBAS data format, please refer to; 
        // RTCA/DO-229C (MOPS), Appendix A.
        //;
        
        static constexpr uint8_t CLASS_ID = 2;
        static constexpr uint8_t MESSAGE_ID = 17;
        
        uint8_t chn;               // Channel Number
        uint8_t svid;              // ID of Satellite transmitting Subframe
        std::array<uint32_t, 10> dwrd;         // Words of Data

    };
}
