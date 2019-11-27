#pragma once

#include <array>
#include <cstdint>

namespace ublox_msgs {
    struct NavRELPOSNED9 {
        // NAV-RELPOSNED (0x01 0x3C);
        // Relative Positioning Information in NED frame
        //;
        // The NED frame is defined as the local topological system at the reference
        // station. The relative position vector components in this message, along with;
        // their associated accuracies, are given in that local topological system
        // This message contains the relative position vector from the Reference Station;
        // to the Rover, including accuracy figures, in the local topological system
        // defined at the reference station;
        //
        // Supported on:;
        //  - u-blox 9 from protocol version 27.11 (only with High Precision GNSS products)
        //;
        
        static constexpr uint8_t CLASS_ID = 1;
        static constexpr uint8_t MESSAGE_ID = 60;
        
        uint8_t version;                     // Message version (0x00 for this version)
        uint8_t reserved1;                   // Reserved
        uint16_t refStationId;               // Reference Station ID. Must be in the range
                                          // 0..4095;
        uint32_t iTow;                       // GPS time of week of the navigation epoch
                                          // [ms];
        
        int32_t relPosN;                     // North component of relative position vector
                                          // [cm];
        int32_t relPosE;                     // East component of relative position vector
                                          // [cm];
        int32_t relPosD;                     // Down component of relative position vector
                                          // [cm];
        int32_t relPosLength;                // Length of the relative position vector
                                          // [cm];
        int32_t relPosHeading;               // Heading of the relative position vector
                                          // [1e-5 deg];
        std::array<uint8_t, 4> reserved2;                // Reserved
        int8_t relPosHPN;                    // High-precision North component of relative
                                          // position vector. [0.1 mm];
                                          // Must be in the range -99 to +99.
                                          // The full North component of the relative;
                                          // position vector, in units of cm, is given by
                                          // relPosN + (relPosHPN * 1e-2);
        int8_t relPosHPE;                    // High-precision East component of relative
                                          // position vector. [0.1 mm];
                                          // Must be in the range -99 to +99.
                                          // The full East component of the relative;
                                          // position vector, in units of cm, is given by
                                          // relPosE + (relPosHPE * 1e-2);
        int8_t relPosHPD;                    // High-precision Down component of relative
                                          // position vector. [0.1 mm];
                                          // Must be in the range -99 to +99.
                                          // The full Down component of the relative;
                                          // position vector, in units of cm, is given by
                                          // relPosD + (relPosHPD * 1e-2);
        int8_t relPosHPLength;               // High-precision component of the length of
                                          // the relative position vector.;
                                          // Must be in the range -99 to +99.
                                          // The full length of the relative position;
                                          // vector, in units of cm, is given by
                                          // relPosLength + (relPosHPLength * 1e-2);
        
        uint32_t accN;                       // Accuracy of relative position North
                                          // component [0.1 mm];
        uint32_t accE;                       // Accuracy of relative position East component
                                          // [0.1 mm];
        uint32_t accD;                       // Accuracy of relative position Down component
                                          // [0.1 mm];
        uint32_t accLength;                  // Accuracy of length of the relative position
                                          // vector [0.1 mm];
        uint32_t accHeading;                 // Accuracy of heading of the relative position
                                          // vector [0.1 mm];
        
        std::array<uint8_t, 4> reserved3;                // Reserved
        
        uint32_t flags;
        static constexpr uint32_t FLAGS_GNSS_FIX_OK = 1;      // A valid fix (i.e within DOP & accuracy
                                          // masks);
        static constexpr uint32_t FLAGS_DIFF_SOLN = 2;        // Set if differential corrections were applied
        static constexpr uint32_t FLAGS_REL_POS_VALID = 4;    // Set if relative position components and
                                          // accuracies are valid;
        static constexpr uint32_t FLAGS_CARR_SOLN_MASK = 24;  // Carrier phase range solution status:
        static constexpr uint32_t FLAGS_CARR_SOLN_NONE = 0;     // No carrier phase range solution
        static constexpr uint32_t FLAGS_CARR_SOLN_FLOAT = 8;    // Float solution. No fixed integer carrier
                                            // phase measurements have been used to;
                                            // calculate the solution
        static constexpr uint32_t FLAGS_CARR_SOLN_FIXED = 16;   // Fixed solution. One or more fixed
                                            // integer carrier phase range measurements;
                                            // have been used to calculate the solution
        static constexpr uint32_t FLAGS_IS_MOVING = 32;       // if the receiver is operating in moving
                                          // baseline mode (not supported in protocol;
                                          // versions less than 20.3)
        static constexpr uint32_t FLAGS_REF_POS_MISS = 64;    // Set if extrapolated reference position was
                                          // used to compute moving baseline solution;
                                          // this epoch (not supported in protocol
                                          // versions less than 20.3);
        static constexpr uint32_t FLAGS_REF_OBS_MISS = 128;   // Set if extrapolated reference observations
                                          // were used to compute moving baseline;
                                          // solution this epoch (not supported in
                                          // protocol versions less than 20.3);
        static constexpr uint32_t FLAGS_REL_POS_HEAD_VALID = 256;   // Set if extrapolated reference observations
                                                // were used to compute moving baseline;
                                                // solution this epoch (not supported in
                                                // protocol versions less than 20.3);
        static constexpr uint32_t FLAGS_REL_POS_NORM = 512;   // Set if extrapolated reference observations
                                          // were used to compute moving baseline;
                                          // solution this epoch (not supported in
                                          // protocol versions less than 20.3);
    };
}
