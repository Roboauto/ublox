#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct EsfRAW_Block {
        // See ESF-RAW;
        
        uint32_t data;      // Its scaling and unit depends on the type and is
                        // the same as in ESF-MEAS;
        static constexpr uint32_t DATA_FIELD_MASK = 16777215;
        static constexpr uint32_t DATA_TYPE_MASK = 4278190080;    // type of data 
                                              // (0 = no data; 1..255 = data type);
        uint32_t sTtag;     // sensor time tag
    };
}
