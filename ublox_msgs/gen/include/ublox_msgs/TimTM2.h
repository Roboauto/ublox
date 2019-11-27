#pragma once

#include <cstdint>

namespace ublox_msgs {
    struct TimTM2 {
        // TIM-TM2 (0x0D, 0x03);
        // Time mark data 
        //;
        // Description for details.
        //; 
        // Supported on:
        //  - u-blox 8 / u-blox M8 with protocol version 22 (only with Timing Products);
        //
        
        static constexpr uint8_t CLASS_ID = 13; 
        static constexpr uint8_t MESSAGE_ID = 3;
        
        uint8_t ch;                     // Channel (i.e. EXTINT) upon which the pulse was measured
        
        uint8_t flags;                   // Bitmask [newRisingEdge, time, utc, timeBase, , newFallingEdge, run, mode]
        static constexpr uint8_t FLAGS_MODE_RUNNING = 1;  // single = 0, running = 1
        static constexpr uint8_t FLAGS_RUN = 2;		// armed = 0, stopped = 1
        static constexpr uint8_t FLAGS_NEWFALLINGEDGE = 4; 	// new falling edge detected
        static constexpr uint8_t FLAGS_TIMEBASE_GNSS = 8;	// 0 = time base is receiver time, 1 = time base is GNSS Time (according to the configuration in CFG-TP5 for tpldx= 0)
        static constexpr uint8_t FLAGS_TIMEBASE_UTC = 16;	// Time Base is UTC (the variant according to the configuration in CFG-NAV5
        static constexpr uint8_t FLAGS_UTC_AVAIL = 32;	// 0 = utc not available, 1 = utc available
        static constexpr uint8_t FLAGS_TIME_VALID = 64;	// 0 = time is not valid, 1 time is valid
        static constexpr uint8_t FLAGS_NEWRISINGEDGE = 128;	// new rising edge detected
        
        uint16_t risingEdgeCount;		// rising edge count
        uint16_t wnR;			// week number of last rising edge
        uint16_t wnF;			// week number of last falling edge
        uint32_t towMsR;			// Tow of rising edge 
        uint32_t towSubMsR;		// Millisecond Fraction of Tow of rising edge in nanoseconds
        uint32_t towMsF;			// tow of falling edge
        uint32_t towSubMsF;		// millisecond fraction of tow of falling edge in nanoseconds
        uint32_t accEst;			// Accuracy estimate

    };
}
