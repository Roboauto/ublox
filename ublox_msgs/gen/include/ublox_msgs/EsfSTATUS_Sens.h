#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct EsfSTATUS_Sens {
        // See Esf-STATUS;
        //
        
        uint8_t sensStatus1;   // Sensor status, part 1 (see graphic below)
        uint8_t sensStatus2;   // Sensor status, part 2 (see graphic below)
        uint8_t freq;          // Observation frequency [Hz]
        uint8_t faults;        // Sensor faults (see graphic below)
    };
}
